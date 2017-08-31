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

#define USE_PREFERRED
const __flash uint16_t	preferred_frequencies_100khz[] = { 1060, 885, 825 };
uint8_t top_rssi[10];
uint16_t top_freq[10];

const __flash char	good_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 !?";

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
	// load preferred stations
	for (uint8_t i = 0; i < ARRAY_SIZE(preferred_frequencies_100khz); i++)
	{
		top_freq[i] = preferred_frequencies_100khz[i];
		top_rssi[i] = 255;
	}

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
* Adjust UTC time to local via 30 minute offset
*/
void rda_adjust_by_offset(uint32_t *d, uint8_t *h, uint8_t *m, int8_t offset)
{
	while (offset > 0)
	{
		(*m) += 30;
		if (*m > 59)
		{
			(*m) -= 60;
			(*h)++;
			if (*h > 23)
			{
				*h = 0;
				(*d)++;
			}
		}
		offset--;
	}

	while (offset < 0)
	{
		(*m) -= 30;
		if (*m > 59)	// underflow
		{
			(*m) += 60;
			(*h)--;
			if (*h > 23)
			{
				(*h) += 24;
				(*d)--;
			}
		}
		offset++;
	}
}

/**************************************************************************************************
* Wait for valid RDS time data. Only returns on timeout.
*/
void rda_wait_for_time(void)
{
	uint8_t confidence = 0;
	uint16_t timeout = 30;		// initial time to get RDA signal
	uint16_t last_blockb = 0;
	char name[9] = "........\0";

	do
	{
		if (RTC_second_tick_SIG)
		{
			RTC_second_tick_SIG = 0;
			if (timeout > 0)
				timeout--;
			printf_P(PSTR("T:%u\r\n"), timeout);
		}

		rda_read_all();
		if ((registers[0x0A] & RDA_RDSR_bm) && (registers[RDA_REG_BLOCKB] != last_blockb))
		{
			last_blockb = registers[RDA_REG_BLOCKB];
			if (((registers[0xA] & RDA_RDSS_bm) == 0) ||	// sync OK
				((registers[0xB] & 0xF) != 0))				// bit errors
			{
				confidence = 0;
				continue;
			}
			if (registers[RDA_REG_BLOCKB] & RDA_ABCD_E_bm)	// not interested
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
					//if ((c1 < 32) || (c1 > 126) || (c2 < 32) || (c2 > 126))
					//	continue;
					if ((strchr_P(good_chars, c1) == NULL) ||
						(strchr_P(good_chars, c2) == NULL))
					{
						confidence = 0;
						continue;
					}
					if (c1 == 32) c1 = '.';
					if (c2 == 32) c2 = '.';
					name[cx] = c1;
					name[cx+1] = c2;

					if (timeout < 60)
						timeout++;

					//printf_P(PSTR("ABCD %04X %04X %04X %04X %s\r\n"),
					//	 registers[0x0C], registers[0x0D], registers[0x0E], registers[0x0F], name);
					printf_P(PSTR("%s\r\n"), name);
				}
				break;
/*
				case 0x2A:	// radiotext
				{
					uint8_t c1, c2;
					c1 = (registers[RDA_REG_BLOCKD] >> 8) & 0x7F;
					c2 = registers[RDA_REG_BLOCKD] & 0x7F;
					if ((strchr_P(good_chars, c1) == NULL) ||
						(strchr_P(good_chars, c2) == NULL))
					{
						confidence = 0;
						continue;
					}
				}
*/
				case 0x4A:	// time
				{
					uint32_t d = (((uint32_t)(registers[RDA_REG_BLOCKB]) & 0b11) << 15) | (registers[RDA_REG_BLOCKC] >> 1);
					uint8_t h = ((registers[RDA_REG_BLOCKC] & 1) << 4) | (registers[RDA_REG_BLOCKD] >> 12);
					uint8_t m = (registers[RDA_REG_BLOCKD] >> 6) & 0x3F;
					int8_t offset = registers[RDA_REG_BLOCKD] & 0x3F;
					if (offset & 0x20) offset |= 0xE0;	// sign extend

					if ((d < 57388) ||		// 01/01/2016
						(d > 88068) ||		// 31/12/2099
						(h > 23) ||
						(m > 59) ||
						(offset < -24) ||	// UTC-12 hours
						(offset > 28))		// UTC+14 hours
					{
						confidence = 0;
						break;
					}

					if (timeout < 60)
						timeout++;

					printf_P(PSTR("MDJ=%lu, h=%u, m=%u, o=%u\r\n"), d, h, m, offset);
					rda_adjust_by_offset(&d, &h, &m, offset);
					printf_P(PSTR("-> %ld %02d:%02d\r\n"), d, h, m);

					if (confidence > 10)
						RTC_set_rds_time(d, h, m);
				}
				break;
			}

			//if (registers[RDA_REG_BLOCKB] & RDA_ABCD_E_bm)
			//	printf_P(PSTR("E    %04X %04X %04X %04X %s\r\n"),
			//			 registers[0x0C], registers[0x0D], registers[0x0E], registers[0x0F], name);
			//else
			//	printf_P(PSTR("ABCD %04X %04X %04X %04X %s\r\n"),
			//			 registers[0x0C], registers[0x0D], registers[0x0E], registers[0x0F], name);

			//printf_P(PSTR("%04X %u\r\n"), registers[0x0B], registers[0x0B] >> 9);
			//_delay_ms(100);
		}
	} while (timeout > 0);

	puts_P(PSTR("RDS timeout"));
	RTC_colon_flash = 0xFF;
}

/**************************************************************************************************
* Scan FM band for stations
*/
void rda_search(void)
{
	memset(top_rssi, 0, sizeof(top_rssi));
	memset(top_freq, 0, sizeof(top_freq));

	// load preferred frequencies
	for (uint8_t i = 0; i < ARRAY_SIZE(preferred_frequencies_100khz); i++)
	{
		top_freq[i] = preferred_frequencies_100khz[i];
		top_rssi[i] = 255;
	}

	// scan FM band
	for (uint16_t i = 870; i < 1070; i++)
	{
		rda_tune(i);
		_delay_ms(250);
		rda_read_reg(RDA_REG_STATUSB);
		uint8_t rssi = registers[RDA_REG_STATUSB] >> 9;
		printf_P(PSTR("%u %04X %u\r\n"), i, registers[RDA_REG_STATUSB], rssi);

		uint8_t lowest_rssi = 0xFF;
		int8_t lowest_idx = -1;
		for (uint8_t j = 0; j < sizeof(top_rssi) / sizeof(top_rssi[0]); j++)
		{
			if (top_rssi[j] < lowest_rssi)
			{
				lowest_rssi = top_rssi[j];
				lowest_idx = j;
			}
		}

		if (lowest_idx == -1) lowest_idx = 0;
		if (top_rssi[lowest_idx] < rssi)
		{
			top_rssi[lowest_idx] = rssi;
			top_freq[lowest_idx] = i;
		}
	}

	// bubble sort with strongest RSSIs first
	bool sorted;
	do
	{
		sorted = true;
		for (uint8_t i = 0; i < (sizeof(top_rssi) / sizeof(top_rssi[0])) - 1; i++)
		{
			if (top_rssi[i] < top_rssi[i+1])
			{
				sorted = false;
				uint8_t rssi = top_rssi[i];
				uint16_t freq = top_freq[i];
				top_rssi[i] = top_rssi[i+1];
				top_freq[i] = top_freq[i+1];
				top_rssi[i+1] = rssi;
				top_freq[i+1] = freq;
			}
		}
	} while (!sorted);

	for (uint8_t i = 0; i < sizeof(top_rssi) / sizeof(top_rssi[0]); i++)
		printf_P(PSTR("%u %u\r\n"), top_freq[i], top_rssi[i]);
}

/**************************************************************************************************
* Continually get the current time from a radio station. Never returns.
*/
void RDA_get_time(void)
{
	TWI_init();
	RDA_init();
	rda_wake();

	RTC_colon_flash = 0xFF;		// flash until RDS time synced

#ifndef USE_PREFERRED
	rda_search();
#endif

	for(;;)
	{
		// try all found frequencies
		for (uint8_t i = 0; i < ARRAY_SIZE(top_freq); i++)
		{
			if (top_freq[i] == 0)
				break;
			if (!rda_tune(top_freq[i]))
				continue;
			printf_P(PSTR("Trying %u...\r\n"), top_freq[i]);

			rda_wait_for_time();
		}

		// all frequencies failed, re-scan
		rda_search();
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

	//rda_search();
	//for (;;);

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

					//printf_P(PSTR("ABCD %04X %04X %04X %04X %s\r\n"),
					//	 registers[0x0C], registers[0x0D], registers[0x0E], registers[0x0F], name);
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
					int8_t offset = registers[RDA_REG_BLOCKD] & 0x3F;
					if (offset & 0x20) offset |= 0xE0;	// sign extend

					if (d < 57978) break;
					if (h > 23) break;
					if (m > 59) break;
					if ((offset < -24) || (offset > 24)) break;
					if (memcmp_P(name, PSTR("Classic."), 8) != 0) break;

					printf_P(PSTR("MDJ=%lu, h=%u, m=%u, o=%u\r\n"), d, h, m, offset);

					// adjust by offset
					while (offset > 0)
					{
						m += 30;
						if (m > 59)
						{
							m -= 60;
							h++;
							if (h > 23)
							{
								h = 0;
								d++;
							}
						}
						offset--;
					}

					while (offset < 0)
					{
						m -= 30;
						if (m > 59)	// underflow
						{
							m += 60;
							h--;
							if (h > 23)
							{
								h += 24;
								d--;
							}
						}
						offset++;
					}

					//printf_P(PSTR("-> %d %02d:%02d\r\n"), d, h, m);
					printf_P(PSTR("-> %ld %02d:%02d\r\n"), d, h, m);
				}
				break;
			}

			//if (registers[RDA_REG_BLOCKB] & RDA_ABCD_E_bm)
			//	printf_P(PSTR("E    %04X %04X %04X %04X %s\r\n"),
			//			 registers[0x0C], registers[0x0D], registers[0x0E], registers[0x0F], name);
			//else
			//	printf_P(PSTR("ABCD %04X %04X %04X %04X %s\r\n"),
			//			 registers[0x0C], registers[0x0D], registers[0x0E], registers[0x0F], name);

			//printf_P(PSTR("%04X %u\r\n"), registers[0x0B], registers[0x0B] >> 9);
			//_delay_ms(100);
		}
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
