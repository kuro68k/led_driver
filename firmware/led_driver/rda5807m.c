/*
 * rda5807m.c
 *
 */ 

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "global.h"
#include "stdio_fast.h"
#include "twi.h"
#include "rtc.h"
#include "rda5807m.h"

const __flash uint16_t	preferred_frequencies_100khz[] = { 885, 825, 1060 };

uint16_t	registers[16];

bool		RDA_time_good = false;


#pragma region Low level control

/**************************************************************************************************
* Write single register
*/
inline void rda_write_reg(uint8_t reg)
{
	TWI_write_reg(RDA_ADDRESS_IDX, reg, &registers[reg], 2);
}

/**************************************************************************************************
* Write all registers
*/
inline void rda_write_all(void)
{
	TWI_write_reg(RDA_ADDRESS_SEQ, RDA_REG_CTRLA, &registers[RDA_REG_CTRLA], 6*2);
}

/**************************************************************************************************
* Read single register
*/
inline void rda_read_reg(uint8_t reg)
{
	TWI_read_reg(RDA_ADDRESS_IDX, reg, &registers[reg], 2);
}

/**************************************************************************************************
* Read sequence of registers
*/
inline void rda_read_seq(uint8_t start_reg, uint8_t end_reg)
{
	TWI_read_reg(RDA_ADDRESS_SEQ, start_reg, &registers[start_reg], (start_reg - end_reg) * 2);
}

/**************************************************************************************************
* Wake up
*/
void rda_wake(void)
{
	registers[RDA_REG_CTRLA] |= RDA_ENABLE_bm;
	rda_write_reg(RDA_REG_CTRLA);
	_delay_ms(100);
}

/**************************************************************************************************
* Sleep
*/
void rda_sleep(void)
{
	registers[RDA_REG_CTRLA] &= ~RDA_ENABLE_bm;
	rda_write_reg(RDA_REG_CTRLA);
}

#pragma endregion

/**************************************************************************************************
* Set up the radio after reset
*/
void RDA_init(void)
{
	TWI_init();
	
	// check chip ID
	uint16_t chipid;
	if (!TWI_read_reg(RDA_ADDRESS_IDX, RDA_REG_CHIPID, &chipid, sizeof(chipid)) ||
		(chipid != 0x58))
	{
		printf("RDA chipid error (0x%04X)\r\n", chipid);
		return;
	}
	
	// soft reset
	registers[RDA_REG_CTRLA] = RDA_SOFT_RESET_bm;
	rda_write_reg(RDA_REG_CTRLA);
	_delay_ms(1);
	
	// initial configuration
/*
	TWI_write_reg(RDA_ADDRESS, RDA_REG_CTRLA,
				  RDA_DIRECT_MODE_bm | RDA_CLK_MODE_32KHZ_gc | RDA_RDS_EN_bm);
	TWI_write_reg(RDA_ADDRESS, RDA_REG_TUNING,
				  (preferred_frequencies_100khz[0] << RDA_CHAN_gp) |
				  RDA_BAND_76_108_WORLD_gc | RDA_SPACE_100KHZ_gc);
	TWI_write_reg(RDA_ADDRESS, RDA_REG_AUDIO, 0);
	TWI_write_reg(RDA_ADDRESS, RDA_REG_CTRLB, 0b1000<<RDA_SEEKTH_gp);
	TWI_write_reg(RDA_ADDRESS, RDA_REG_OPEN, 0);
	TWI_write_reg(RDA_ADDRESS, RDA_REG_BAND, 0);
*/

	registers[RDA_REG_CTRLA] = RDA_DIRECT_MODE_bm | RDA_CLK_MODE_32KHZ_gc | RDA_RDS_EN_bm;
	registers[RDA_REG_TUNING] = RDA_BAND_76_108_WORLD_gc | RDA_SPACE_100KHZ_gc;
	registers[RDA_REG_AUDIO] = 0;
	registers[RDA_REG_CTRLB] = 0b1000<<RDA_SEEKTH_gp;
	registers[RDA_REG_OPEN] = 0;
	registers[RDA_REG_BAND] = 0;
	rda_write_all();
}

/**************************************************************************************************
* Tune to a specific frequency in multiples of 100kHz (e.g. 92.5MHz = 925)
*/
bool rda_tune(uint16_t freq)
{
	printf_P(PSTR("Tuning to %u... "), freq);

	// start seeking
	registers[RDA_REG_TUNING] = (registers[RDA_REG_TUNING] & ~RDA_CHAN_gm) |
								((freq - 760) << RDA_CHAN_gp) |
								RDA_TUNE_bm;
	rda_write_reg(RDA_REG_TUNING);
	
	// wait for completion
	do
	{
		_delay_ms(10);
		rda_read_reg(RDA_REG_STATUSA);
	} while (!(registers[RDA_REG_STATUSA] & (RDA_STC_bm | RDA_SF_bm)));		// seek complete or failed
	
	if (registers[RDA_REG_STATUSA] & RDA_SF_bm)
	{
		puts_P(PSTR("failed"));
		return false;
	}
	puts_P(PSTR("OK"));
	return true;
}

/**************************************************************************************************
* Seek up to find stations. Restart starts the search from the bottom of the FM band.
*/
bool rda_seek_up(bool restart)
{
	if (restart)
	{
		puts_P(PSTR("Restarting seek"));
		if (!rda_tune(760))	// go to bottom of the FM band
			return false;
	}

	// start seeking
	puts_P(PSTR("Seeking up"));
	registers[RDA_REG_CTRLA] |= RDA_SEEKUP_bm | RDA_SEEK_bm;
	rda_write_reg(RDA_REG_CTRLA);
	
	// wait for completion
	do
	{
		_delay_ms(10);
		rda_read_reg(RDA_REG_STATUSA);
	} while (!(registers[RDA_REG_STATUSA] & (RDA_STC_bm | RDA_SF_bm)));		// seek complete or failed
	
	if (registers[RDA_REG_STATUSA] & RDA_SF_bm)
	{
		puts_P(PSTR("Seek failed"));
		return false;
	}
	
	printf("Found station at %u\r\n", (registers[RDA_REG_STATUSA] & 0x1F) + 760);
	return true;
}

/**************************************************************************************************
* Wait for valid RDS time data. Only returns on timeout.
*/
void rda_wait_for_time(void)
{
	uint16_t timeout = 0;
	uint16_t max_timeout = 10;	// initially 10 seconds to get RDS signal
	
	do
	{
		if (RTC_second_tick_SIG)
		{
			RTC_second_tick_SIG = 0;
			timeout++;
		}
		
		rda_read_reg(RDA_REG_STATUSA);
		if (registers[RDA_REG_STATUSA] & RDA_RDSR_bm)
		{
			if (max_timeout == 10)	// first time RDS found
			{
				puts_P(PSTR("RDS found"));
				timeout = 0;
				max_timeout = 65;	// time broadcast once a minute
			}

			rda_read_seq(RDA_REG_BLOCKB, RDA_REG_BLOCKD);
			uint8_t type = 0x0A | (registers[RDA_REG_BLOCKB] >> 8) | (registers[RDA_REG_BLOCKB] >> 11);
			if (type == 0x4A)	// time+date
			{
				puts_P(PSTR("RDS time/date received"));
				// modified Julian date offset from 1900
				uint32_t mjd = (uint32_t)(registers[RDA_REG_BLOCKB] & 0b11) << 16;
				mjd |= registers[RDA_REG_BLOCKC] >> 1;
				uint8_t hour = (registers[RDA_REG_BLOCKC] & 1) << 4;
				hour |= registers[RDA_REG_BLOCKD] >> 12;
				uint8_t minute = (registers[RDA_REG_BLOCKD] >> 5) & 0x1F;
				int8_t offset = (registers[RDA_REG_BLOCKD] & 0x1F);
				if (offset & 0x10)	// need to sign extend
					offset |= 0xF0;

				printf_P(PSTR("%lu %02u:%02u:%02u %+d\r\n"));
				
				if (RTC_set_rds_time(mjd, hour, minute, offset))
				{
					max_timeout = 310;		// this station works, ignore temporary interference
					RTC_colon_flash = 0;	// indicate time good
				}
				else
					puts_P(PSTR("Error setting time"));
			}
		}
		
		_delay_ms(10);		// limit polling rate
		
	} while (timeout < max_timeout);
	
	puts_P(PSTR("RDS timeout"));
	RTC_colon_flash = 0xFF;
}

/**************************************************************************************************
* Continually get the current time from a radio station. Never returns.
*/
void RDA_get_time(void)
{
	rda_wake();

	uint8_t	freq_idx = 0;
	RTC_colon_flash = 0xFF;		// flash until RDS time synced
	
	for(;;)
	{
		// tune to next station to try
		if (freq_idx < ARRAY_SIZE(preferred_frequencies_100khz))	// use a preferred frequency
		{
			if (!rda_tune(preferred_frequencies_100khz[freq_idx]))
			{
				freq_idx++;
				continue;
			}
		}
		else														// search for stations
		{
			bool res;
			if (freq_idx == ARRAY_SIZE(preferred_frequencies_100khz))	// first time
				res = rda_seek_up(true);
			else
				res = rda_seek_up(false);
			if (!res)	// failed to find any stations
			{
				freq_idx = 0;	// restart
				continue;
			}
			freq_idx++;
		}
		
		// try to get time from RDS
		rda_wait_for_time();
	}
}
