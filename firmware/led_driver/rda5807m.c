/*
 * rda5807m.c
 *
 */ 

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <string.h>
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
void rda_write_reg(uint8_t reg)
{
	uint16_t big_endian = (registers[reg] >> 8) | (registers[reg] << 8);
	TWI_write_reg(RDA_ADDRESS_IDX, reg, (uint8_t *)&big_endian, 2);
}

/**************************************************************************************************
* Write all registers
*/
void rda_write_all(void)
{
	uint16_t big_endian[6];
	big_endian[0] = (registers[2] >> 8) | (registers[2] << 8);
	big_endian[1] = (registers[3] >> 8) | (registers[3] << 8);
	big_endian[2] = (registers[4] >> 8) | (registers[4] << 8);
	big_endian[3] = (registers[5] >> 8) | (registers[5] << 8);
	big_endian[4] = (registers[6] >> 8) | (registers[6] << 8);
	big_endian[5] = (registers[7] >> 8) | (registers[7] << 8);
	TWI_write_reg(RDA_ADDRESS_SEQ, RDA_REG_CTRLA, (uint8_t *)&big_endian, 6*2);
}

/**************************************************************************************************
* Read single register
*/
bool rda_read_reg(uint8_t reg)
{
	bool res = TWI_read_reg(RDA_ADDRESS_IDX, reg, (uint8_t *)&registers[reg], 2);
	if (res)
		registers[reg] = (registers[reg] >> 8) | (registers[reg] << 8);
	return res;
}

/**************************************************************************************************
* Read status A and B registers
*/
bool rda_read_statusAB(void)
{
	bool res = TWI_read(RDA_ADDRESS_SEQ, (uint8_t *)&registers[0x0A], 2*2);
	if (res)
	{
		registers[0x0A] = (registers[0x0A] >> 8) | (registers[0x0A] << 8);
		registers[0x0B] = (registers[0x0B] >> 8) | (registers[0x0B] << 8);
	}
	return res;
}

/**************************************************************************************************
* Read all data registers (0x0A-0x0F)
*/
bool rda_read_all(void)
{
	bool res = TWI_read(RDA_ADDRESS_SEQ, (uint8_t *)&registers[0x0A], 6*2);
	if (res)
	{
		registers[0x0A] = (registers[0x0A] >> 8) | (registers[0x0A] << 8);
		registers[0x0B] = (registers[0x0B] >> 8) | (registers[0x0B] << 8);
		registers[0x0C] = (registers[0x0C] >> 8) | (registers[0x0C] << 8);
		registers[0x0D] = (registers[0x0D] >> 8) | (registers[0x0D] << 8);
		registers[0x0E] = (registers[0x0E] >> 8) | (registers[0x0E] << 8);
		registers[0x0F] = (registers[0x0F] >> 8) | (registers[0x0F] << 8);
	}
	return res;
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
	for (int retries = 0; retries < 5; retries++)
	{
		TWI_init();

		// soft reset
		registers[RDA_REG_CTRLA] = RDA_SOFT_RESET_bm;
		rda_write_reg(RDA_REG_CTRLA);
		_delay_ms(1);
	
		// check chip ID
		if (!rda_read_reg(RDA_REG_CHIPID) ||
			((registers[RDA_REG_CHIPID] & 0xFF00) != 0x5800))
			printf("RDA chipid error (0x%04X)\r\n", registers[RDA_REG_CHIPID]);
		else
			break;
	}

	// initial configuration
	registers[RDA_REG_CTRLA] =	RDA_DHIZ_bm |
								//RDA_DMUTE_bm |
								//RDA_MONO_bm |
								RDA_RCLK_DIRECT_bm |
								RDA_CLK_MODE_32KHZ_gc |
								RDA_NEW_METHOD_bm |
								RDA_RDS_EN_bm |
								RDA_ENABLE_bm;
	//registers[RDA_REG_CTRLA] = RDA_CLK_MODE_32KHZ_gc | RDA_RDS_EN_bm;
	//registers[RDA_REG_TUNING] = RDA_BAND_76_108_WORLD_gc | RDA_SPACE_100KHZ_gc;
/*
	registers[RDA_REG_TUNING] = RDA_BAND_87_108_EU_US_gc | RDA_SPACE_100KHZ_gc;
	registers[RDA_REG_AUDIO] = (1<<11) | (1<<9);
	registers[RDA_REG_CTRLB] = 0b1000<<RDA_SEEKTH_gp;
	registers[RDA_REG_CTRLB] = (0b0110<<RDA_SEEKTH_gp) | 0b1101;
	registers[RDA_REG_OPEN] = 0;
	registers[RDA_REG_BAND] = 0;
*/
	// programming guide
	//registers[0x02] = 0xC001;
	registers[0x03] = 0x1B90;
	registers[0x04] = 0x0C00;	// bit 10 undocumented
	registers[0x05] = RDA_INT_MODE_bm |	// seems to be essential
					  RDA_LNA_PORT_LNAP_gc |
					  RDA_LNA_ICSEL_2_7MA_gc |
					  0xD;	// volume
					  //0x86AD;
	registers[0x06] = 0x8000;	// reserved bit set
	//registers[0x07] = 0x5F1A;
	//registers[0x08] = 0x5EC6;

	rda_write_all();
	_delay_ms(600);
}

/**************************************************************************************************
* Tune to a specific frequency in multiples of 100kHz (e.g. 92.5MHz = 925)
*/
bool rda_tune(uint16_t freq)
{
	//printf_P(PSTR("Tuning to %u... "), freq);

	// start seeking
	registers[RDA_REG_TUNING] = (registers[RDA_REG_TUNING] & ~RDA_CHAN_gm) |
								((freq - 870) << RDA_CHAN_gp) |
								RDA_TUNE_bm;
	registers[RDA_REG_TUNING] = ((freq - 870) << 6) | RDA_TUNE_bm;
	rda_write_reg(RDA_REG_TUNING);
	
	// wait for completion
	uint8_t timeout = 0;
	do
	{
		_delay_ms(10);
		rda_read_reg(RDA_REG_STATUSA);
		timeout++;
		if (timeout > 250)
			break;
	} while (!(registers[RDA_REG_STATUSA] & (RDA_STC_bm | RDA_SF_bm)));		// seek complete or failed

	//rda_read_reg(RDA_REG_TUNING);
	//puts("");
	//printf_P(PSTR("TUNING:  %04X\r\n"), registers[RDA_REG_TUNING]);
	//printf_P(PSTR("STATUSA: %04X\r\n"), registers[RDA_REG_STATUSA]);
	
	if (registers[RDA_REG_STATUSA] & RDA_SF_bm)
	{
		puts_P(PSTR("failed"));
		return false;
	}
	//puts_P(PSTR("OK"));
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
	uint8_t timeout = 0;
	do
	{
		_delay_ms(50);	// 12.5 seconds timeout
		//if (!rda_read_reg(RDA_REG_STATUSA))
		//	putchar('X');
		//rda_read_statusAB();
		//printf_P(PSTR("%04X\r\n"), registers[RDA_REG_STATUSA]);
		rda_read_reg(RDA_REG_TUNING);
		printf_P(PSTR("%04X\r\n"), registers[RDA_REG_TUNING]);
		timeout++;
		if (timeout > 250)
			break;
		rda_read_reg(RDA_REG_STATUSA);
	} while (!(registers[RDA_REG_STATUSA] & (RDA_STC_bm | RDA_SF_bm)));		// seek complete or failed
	
	if (registers[RDA_REG_STATUSA] & RDA_SF_bm)
	{
		puts_P(PSTR("Seek failed"));
		return false;
	}
	
	rda_read_statusAB();
	printf("STATUSA: %04X\r\n", registers[RDA_REG_STATUSA]);
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

			rda_read_all();
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

/**************************************************************************************************
* Test code
*/
void RDA_test(void)
{
	TWI_init();

	RDA_init();
	rda_wake();

	//rda_seek_up(false);
	rda_tune(1004);
	
	_delay_ms(1000);
	rda_read_reg(RDA_REG_STATUSB);
	printf_P(PSTR("STATUSB: %04X %u\r\n"), registers[RDA_REG_STATUSB], registers[RDA_REG_STATUSB] >> 9);
/*
	uint16_t temp = registers[RDA_REG_STATUSB];
	for(;;)
	{
		rda_read_reg(RDA_REG_STATUSB);
		if (temp != registers[RDA_REG_STATUSB])
		{
			temp = registers[RDA_REG_STATUSB];
			printf_P(PSTR("%04X\r\n"), temp);
		}
	}
*/

	uint16_t last_blockb = 0;
	char name[9] = "........\0";
	//char radiotext[65] = "................................................................\0";
	for(;;)
	{
		//_delay_ms(10);
		rda_read_all();
		if ((registers[0x0A] & RDA_RDSR_bm) && (registers[RDA_REG_BLOCKB] != last_blockb))
		{
			last_blockb = registers[RDA_REG_BLOCKB];
			if ((registers[0xA] & RDA_RDSS_bm) == 0)
				continue;
			if ((registers[0xB] & 0xF) != 0)
				continue;
			if (registers[RDA_REG_BLOCKB] & RDA_ABCD_E_bm)
				continue;

			uint8_t group_type = 0x0A |
								((registers[RDA_REG_BLOCKB] & 0xF000) >> 8) |
								((registers[RDA_REG_BLOCKB] &0x0800) >> 8);		// A/B bit
			switch (group_type)
			{
				case 0x0A:	// station name, PI code etc
				case 0x0B:
				{
					uint8_t cx = registers[RDA_REG_BLOCKB] & 0b11;
					cx *= 2;
					uint8_t c1, c2;
					c1 = (registers[RDA_REG_BLOCKD] >> 8) & 0x7F;
					c2 = registers[RDA_REG_BLOCKD] & 0x7F;
					if ((c1 < 32) || (c1 > 126) || (c2 < 32) || (c2 > 126))
						continue;
					if (c1 == 32) c1 = '.';
					if (c2 == 32) c2 = '.';
					name[cx] = c1;
					name[cx+1] = c2;
				}
				break;
/*
				case 0x2A:	// radiotext
				{
					uint8_t cx = registers[RDA_REG_BLOCKB] & 0b11111;
					cx *= 2;
					uint8_t c1, c2;
					c1 = (registers[RDA_REG_BLOCKD] >> 8) & 0x7F;
					c2 = registers[RDA_REG_BLOCKD] & 0x7F;
					if ((c1 < 32) || (c1 > 126) || (c2 < 32) || (c2 > 126))
						continue;
					if (c1 == 32) c1 = '.';
					if (c2 == 32) c2 = '.';
					radiotext[cx] = c1;
					radiotext[cx+1] = c2;
				}
*/
				case 0x4A:	// time
				{
					uint32_t d = (((uint32_t)(registers[RDA_REG_BLOCKB]) & 0b11) << 15) | (registers[RDA_REG_BLOCKC] >> 1);
					uint8_t h = ((registers[RDA_REG_BLOCKC] & 1) << 4) | (registers[RDA_REG_BLOCKD] >> 12);
					uint8_t m = (registers[RDA_REG_BLOCKD] >> 6) & 0x3F;
					
					if (d < 57978) break;
					if (h > 23) break;
					if (m > 59) break;
					if (memcmp_P(name, PSTR("Classic."), 8) != 0) break;
					
					printf_P(PSTR("MDJ=%lu, h=%u, m=%u\r\n"), d, h, m);
				}
				break;
			}

			//if (registers[RDA_REG_BLOCKB] & RDA_ABCD_E_bm)
			//	printf_P(PSTR("E    %04X %04X %04X %04X %s\r\n"),
			//			 registers[0x0C], registers[0x0D], registers[0x0E], registers[0x0F], name);
			//else
				printf_P(PSTR("ABCD %04X %04X %04X %04X %s\r\n"),
						 registers[0x0C], registers[0x0D], registers[0x0E], registers[0x0F], name);

			//printf_P(PSTR("%04X %u\r\n"), registers[0x0B], registers[0x0B] >> 9);
			//_delay_ms(100);
		}
	}

	for (uint16_t i = 870; i < 1070; i++)
	{
		rda_tune(i);
		_delay_ms(100);
		rda_read_reg(RDA_REG_STATUSB);
		printf_P(PSTR("%u %04X %u\r\n"), i, registers[RDA_REG_STATUSB], registers[RDA_REG_STATUSB] >> 9);
	}
	
	
/*	
	rda_read_all();
	
	for(uint8_t i = 0; i < 16; i++)
		printf_P(PSTR("%04X\r\n"), registers[i]);

	bool res = rda_read_reg(RDA_REG_CHIPID);
	printf_P(PSTR("ID: %04X\r\n"), registers[0]);
	if (res) puts_P(PSTR("OK"));
	else puts_P(PSTR("FAIL"));
*/	
	for(;;);
}
