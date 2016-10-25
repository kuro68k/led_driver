/*
 * as1116.h
 *
 */ 


#ifndef AS1116_H_
#define AS1116_H_


#define AS_NUM_DEVICES				2

#define AS_SPI						SPIC
#define AS_PORT						PORTC
#define AS_LD_PIN_bm				PIN4_bm


// serial interface
#define AS_REG_NOP					0x00
#define AS_REG_DIGIT0				0x01
#define AS_REG_DIGIT1				0x02
#define AS_REG_DIGIT2				0x03
#define AS_REG_DIGIT3				0x04
#define AS_REG_DIGIT4				0x05
#define AS_REG_DIGIT5				0x06
#define AS_REG_DIGIT6				0x07
#define AS_REG_DIGIT7				0x08
#define AS_REG_DECODE_MODE			0x09
#define AS_REG_GLOBAL_INTENTSITY	0x0A
#define AS_REG_SCAN_LIMIT			0x0B
#define AS_REG_SHUTDOWN				0x0C
#define AS_REG_FEATURE				0x0E
#define AS_REG_DISPLAY_TEST_MODE	0x0F
#define AS_REG_DIG01_INTENSITY		0x10
#define AS_REG_DIG23_INTENSITY		0x11
#define AS_REG_DIG45_INTENSITY		0x12
#define AS_REG_DIG67_INTESITY		0x13

#define AS_WRITE_BIT_bm				(1<<6)

// feature register
#define AS_CLK_EN_bm				(1<<0)
#define AS_REG_RES_bm				(1<<1)
#define AS_DECODE_SEL_bm			(1<<2)
#define AS_BLINK_EN_bm				(1<<4)
#define AS_BLINK_FREQ_SEL_bm		(1<<5)
#define AS_SYNC_bm					(1<<6)
#define AS_BLINK_START_bm			(1<<7)

// shutdown register
#define AS_SHUTDOWN_MODE_RESET		(0x00)
#define AS_SHUTDOWN_MODE			(0x80)
#define AS_NORMAL_MODE_RESET		(0x01)
#define AS_NORMAL_MODE				(0x81)



extern void AS_write_digit_all(uint8_t digit, const uint8_t *data);
extern void AS_init(void);



#endif /* AS1116_H_ */