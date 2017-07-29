/*
 * led_driver.c
 *
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "global.h"
#include "stdio_fast.h"
#include "rtc.h"
#include "as1116.h"
#include "rda5807m.h"

typedef struct {
	char		magic_string[8];
	uint8_t		version_major;
	uint8_t		version_minor;
	uint8_t		mcu_signature[3];
	uint32_t	flash_size_b;
	uint16_t	page_size_b;
	uint32_t	eeprom_size_b;
	uint16_t	eeprom_page_size_b;
} FW_INFO_t;


#define VERSION_MAJOR	0
#define VERSION_MINOR	1

// data embedded in firmware image so that the bootloader program can read it
volatile const __flash FW_INFO_t firmware_info =	{	{ 0x59, 0x61, 0x6d, 0x61, 0x4e, 0x65, 0x6b, 0x6f },		// "YamaNeko" magic identifier
														VERSION_MAJOR,
														VERSION_MINOR,
														{ SIGNATURE_0, SIGNATURE_1, SIGNATURE_2 },
														APP_SECTION_SIZE,
														APP_SECTION_PAGE_SIZE,
														EEPROM_SIZE,
														EEPROM_PAGE_SIZE
													};

int main(void)
{
	firmware_info.magic_string[0];	// prevent firmware_info being optimized away

	// port A
	PORTA.OUT = 0;
	PORTA.DIR = 0xFF;
	
	// port C, radio and debug comms
	PORTC.OUT = PIN0_bm | PIN1_bm | PIN3_bm;	// TWI, TX
	PORTC.DIR = 0xFF;
	
	// port D, expansion and AS1116 drivers
	PORTD.OUT = 0xFF;
	PORTD.DIR = 0xFF;
	
	// port R,  clocks
	PORTR.OUT = 0;
	PORTR.DIR = PIN0_bm;	// 32.768kHz output
	PORTCFG.CLKOUT = PORTCFG_RTCOUT_PR0_gc;

	STDIO_init();
	puts_P(PSTR("RDA test"));
	RDA_test();

	//AS_init();
	//RTC_init();

	PMIC.CTRL = PMIC_RREN_bm | PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
	sei();
	SLEEP.CTRL = SLEEP_SMODE_IDLE_gc | SLEEP_SEN_bm;

	RTC_show_clock = 0xFF;
	RDA_get_time();
}

