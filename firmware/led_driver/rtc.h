/*
 * rtc.h
 *
 */


#ifndef RTC_H_
#define RTC_H_


typedef struct
{
	uint8_t	day, month, year;
	uint8_t	hour, minute, second;
} RTC_time_t;


/**************************************************************************************************
* Is year a leap year? Only works for 2000-2099.
*/
static inline bool RTC_is_leap_year(uint8_t year)
{
	if ((year & 0b11) == 0)
		return true;
	return false;
}


extern volatile uint8_t	RTC_second_tick_SIG;
extern volatile uint8_t	RTC_show_clock;
extern volatile uint8_t	RTC_colon_flash;


extern void RTC_set_rds_time(uint32_t mjd, uint8_t hour, uint8_t minute);
extern void RTC_get_time(RTC_time_t *time);
extern void RTC_init(void);


#endif /* RTC_H_ */