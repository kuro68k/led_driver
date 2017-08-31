/*
 * rtc.c
 *
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>
#include "global.h"
#include "stdio_fast.h"
#include "rtc.h"
#include "clock.h"

const __flash uint8_t days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

// variables accessed by interrupts
volatile RTC_time_t	rtc_time_AT;
volatile uint8_t	RTC_second_tick_SIG = 0;
volatile uint8_t	RTC_show_clock = 0;
volatile uint8_t	RTC_colon_flash = 0;

uint32_t	rtc_last_mjd = -1;
RTC_time_t	rtc_last_mjd_conversion;


/**************************************************************************************************
* Validate time from RDS receiver. mjd is modified Julian date.
*/
bool rtc_check_rds_time(uint32_t mjd, uint8_t hour, uint8_t minute, int8_t offset)
{
	if ((minute > 59) || (hour > 23) || (offset > 14) || (offset < -14))
		return false;

	if ((mjd < 57388) ||	// 01/01/2016
		(mjd > 88068))		// 31/12/2099
		return false;
	return true;
}

/**************************************************************************************************
* Convert modified Julian day to Gregorian calendar. Adapted from Fliegel/van Flandern
* ACM 11/#10 p 657 Oct 1968.
*/
void rtc_mjd_to_dmy(uint32_t mjd, uint8_t *day, uint8_t *month, uint8_t *year)
{
	int j, c, y, m;
	j = mjd + 2400001 + 68569;
	c = 4 * j / 146097;
	j = j - (146097 * c + 3) / 4;
	y = 4000 * (j + 1) / 1461001;
	j = j - 1461 * y / 4 + 31;
	m = 80 * j / 2447;
	*day = j - 2447 * m / 80;
	j = m / 11;
	*month = m + 2 - (12 * j);
	*year = 100 * (c - 49) + y + j;
}

/**************************************************************************************************
* Convert and set time from RDS receiver
*/
void RTC_set_rds_time(uint32_t mjd, uint8_t hour, uint8_t minute)
{
	// set new time
	RTC_time_t	new_time;
	rtc_mjd_to_dmy(mjd, &new_time.day, &new_time.month, &new_time.year);
	new_time.hour = hour;
	new_time.minute = minute;
	new_time.second = 0;

	// set RTC
	cli();
	memcpy((void *)&rtc_time_AT, &new_time, sizeof(rtc_time_AT));
	sei();

	// update display
	if (RTC_show_clock)
	{
		RTC_show_clock = 0;
		CLK_display_time(&new_time);
		RTC_show_clock = 0xFF;
	}
}

/**************************************************************************************************
* Get current time
*/
void RTC_get_time(RTC_time_t *time)
{
	cli();
	memcpy(time, (void *)&rtc_time_AT, sizeof(rtc_time_AT));
	sei();
}

/**************************************************************************************************
* Start the RTC after reset
*/
void RTC_init(void)
{
	RTC.CTRL = 0;							// make sure RTC isn't running

	// initial time after reset
	rtc_time_AT.day = 1;
	rtc_time_AT.month = 1;
	rtc_time_AT.year = 16;
	rtc_time_AT.hour = 0;
	rtc_time_AT.minute = 0;
	rtc_time_AT.second = 0;

	// start RTC
	//CLK.RTCCTRL = CLK_RTCSRC_EXTCLK_gc | CLK_RTCEN_bm;	// 32.768kHz from TCXO
	OSC.CTRL |= OSC_RC32KEN_bm;
	while(!(OSC.STATUS & OSC_RC32KRDY_bm));
	CLK.RTCCTRL = CLK_RTCSRC_RCOSC32_gc | CLK_RTCEN_bm;

	while ((!RTC.STATUS & RTC_SYNCBUSY_bm));
	//RTC.INTCTRL = RTC_OVFINTLVL_LO_gc | RTC_COMPINTLVL_LO_gc;
	RTC.CALIB = 0;
	RTC.CNT = 0;
	RTC.PER = 32768;
	RTC.COMP = 16384;
	RTC.CTRL = RTC_PRESCALER_DIV1_gc;
}

/**************************************************************************************************
* RTC 1 second tick interrupt handler
*/
ISR(RTC_OVF_vect)
{
	rtc_time_AT.second++;
	if (rtc_time_AT.second > 59)
	{
		rtc_time_AT.second = 0;
		rtc_time_AT.minute++;
		if (rtc_time_AT.minute > 59)
		{
			rtc_time_AT.minute = 0;
			rtc_time_AT.hour++;
			if (rtc_time_AT.hour > 23)
			{
				rtc_time_AT.hour = 0;
				rtc_time_AT.day++;

				uint8_t d = days_in_month[rtc_time_AT.month - 1];
				if ((rtc_time_AT.month == 2) &&
					(RTC_is_leap_year(rtc_time_AT.year)))
					d++;
				if (rtc_time_AT.day > d)
				{
					rtc_time_AT.day = 1;
					rtc_time_AT.month++;
					if (rtc_time_AT.month > 12)
					{
						rtc_time_AT.month = 1;
						rtc_time_AT.year++;
					}
				}
			}
		}
	}

	if (RTC_show_clock)
		CLK_display_time((RTC_time_t *)&rtc_time_AT);
}

/**************************************************************************************************
* 2Hz flashing colons
*/
ISR(RTC_COMP_vect)
{
	if (RTC_show_clock && RTC_colon_flash)
		CLK_colons_off();
}
