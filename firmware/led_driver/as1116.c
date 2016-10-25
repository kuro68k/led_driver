/*
 * as1116.c
 *
 */ 

#include <avr/io.h>
#include "global.h"
#include "as1116.h"


/**************************************************************************************************
* Low level SPI write
*/
inline void as_spi_write(uint8_t w)
{
	AS_SPI.STATUS = SPI_TXCIF_bm;				// clear FIFO empty flag
	while(!(AS_SPI.STATUS & SPI_DREIF_bm));		// wait for FIFO slot
	AS_SPI.DATA = w;
}

/**************************************************************************************************
* Write a single AS1116's register. Device is the device number in the chain.
*/
void AS_write_single(uint8_t device, uint8_t reg, uint8_t data)
{
	AS_PORT.OUTCLR = AS_LD_PIN_bm;
	
	// pad to target device
	while (device--)
	{
		as_spi_write(0x00);
		as_spi_write(AS_REG_NOP | AS_WRITE_BIT_bm);
	}
	
	as_spi_write(data);
	as_spi_write(reg | AS_WRITE_BIT_bm);
	while(!(AS_SPI.STATUS & SPI_TXCIF_bm));		// wait for last byte to clear FIFO
	
	AS_PORT.OUTSET = AS_LD_PIN_bm;
}

/**************************************************************************************************
* Write register on all AS1116s.
*/
void AS_write_all(uint8_t reg, uint8_t data)
{
	AS_PORT.OUTCLR = AS_LD_PIN_bm;
	
	for (uint8_t i = 0; i < AS_NUM_DEVICES; i++)
	{
		as_spi_write(data);
		as_spi_write(reg | AS_WRITE_BIT_bm);
	}
	while(!(AS_SPI.STATUS & SPI_TXCIF_bm));		// wait for last byte to clear FIFO
	
	AS_PORT.OUTSET = AS_LD_PIN_bm;
}

/**************************************************************************************************
* Write digit on all AS1116s
*/
void AS_write_digit_all(uint8_t digit, const uint8_t *data)
{
	digit += AS_REG_DIGIT0;
	for (uint8_t i = 0; i < AS_NUM_DEVICES; i++)
	{
		as_spi_write(*data++);
		as_spi_write(digit | AS_WRITE_BIT_bm);
	}
}

/**************************************************************************************************
* Set up AS1116 after reset
*/
void AS_init(void)
{
	// set up SPI port
	AS_SPI.CTRL = 0;
	AS_SPI.CTRLB = SPI_BUFMODE_BUFMODE2_gc | SPI_SSD_bm;	// disable slave select
	AS_SPI.INTCTRL = 0;
	AS_SPI.CTRL = SPI_CLK2X_bm | SPI_ENABLE_bm | SPI_MASTER_bm |
				  SPI_DORD_bm | SPI_MODE_1_gc | SPI_PRESCALER_DIV4_gc;
	
	AS_write_all(AS_REG_FEATURE, AS_REG_RES_bm);			// reset settings to default
	AS_write_all(AS_REG_SHUTDOWN, AS_SHUTDOWN_MODE_RESET);
}
