/*
 * clock.c
 *
 */ 

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include "global.h"
#include "as1116.h"
#include "rtc.h"
#include "clock.h"


extern const __flash uint16_t segbmp[];


/**************************************************************************************************
* Update display with current time
*/
void CLK_display_time(const RTC_time_t *time)
{
	uint8_t	digits[8];
	clk_bin2dec(time->hour, &digits[0], &digits[1]);
	clk_bin2dec(time->minute, &digits[2], &digits[3]);
	clk_bin2dec(time->second, &digits[4], &digits[5]);
	digits[7] = 0xFF;

	for (uint8_t i = 0; i < 8; i++)
	{
		uint16_t bmp = segbmp[digits[i] + '0'];		// copy from flash to RAM
		AS_write_digit_all(i, (uint8_t *)&bmp);
	}
}

void CLK_colons_off(void)
{
	uint16_t d = 0;
	AS_write_digit_all(7, (uint8_t *)&d);
}