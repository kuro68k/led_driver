/*
 * rda5807m.h
 *
 */ 


#ifndef RDA5807M_H_
#define RDA5807M_H_


#define RDA_ADDRESS_SEQ				0x10
#define RDA_ADDRESS_IDX				0x11


// RDA5806M registers
#define RDA_REG_CHIPID				0x00
#define RDA_REG_CTRLA				0x02
#define RDA_REG_TUNING				0x03
#define RDA_REG_AUDIO				0x04
#define RDA_REG_CTRLB				0x05
#define RDA_REG_OPEN				0x06
#define RDA_REG_BAND				0x07
#define RDA_REG_STATUSA				0x0A
#define RDA_REG_STATUSB				0x0B
#define RDA_REG_BLOCKA				0x0C
#define RDA_REG_BLOCKB				0x0D
#define RDA_REG_BLOCKC				0x0E
#define RDA_REG_BLOCKD				0x0F


// CHIPID
#define RDA_CHIPID_gc				0xFE00

// CTRLA
#define RDA_DHIZ_bm					(1<<15)
#define RDA_DMUTE_bm				(1<<14)
#define RDA_MONO_bm					(1<<13)
#define RDA_RCLK_NON_CAL_bm			(1<<11)
#define RDA_RCLK_DIRECT_bm			(1<<10)
#define RDA_SEEKUP_bm				(1<<9)
#define RDA_SEEK_bm					(1<<8)
#define RDA_SKMODE_bm				(1<<7)
#define RDA_CLK_MODE_gp				4
#define RDA_CLK_MODE_gm				(0b111<<RDA_CLK_MODE_gp)
#define RDA_CLK_MODE_32KHZ_gc		(0b000<<RDA_CLK_MODE_gp)
#define RDA_CLK_MODE_12MHZ_gc		(0b001<<RDA_CLK_MODE_gp)
#define RDA_CLK_MODE_24MHZ_gc		(0b101<<RDA_CLK_MODE_gp)
#define RDA_RDS_EN_bm				(1<<3)
#define RDA_NEW_METHOD_bm			(1<<2)
#define RDA_SOFT_RESET_bm			(1<<1)
#define RDA_ENABLE_bm				(1<<0)

// TUNING
#define	RDA_CHAN_gp					6
#define RDA_CHAN_gm					(0x1F>>RDA_CHAN_gp)
#define RDA_DIRECT_MODE_bm			(1<<5)
#define RDA_TUNE_bm					(1<<4)
#define RDA_BAND_gp					2
#define RDA_BAND_gm					(0b11<<RDA_BAND_gp)
#define RDA_BAND_87_108_EU_US_gc	(0b00<<RDA_BAND_gp)
#define RDA_BAND_76_91_JAPAN_gc		(0b01<<RDA_BAND_gp)
#define RDA_BAND_76_108_WORLD_gc	(0b10<<RDA_BAND_gp)
#define RDA_BAND_65_76_EAST_gc		(0b11<<RDA_BAND_gp)
#define RDA_SPACE_gp				0
#define RDA_SPACE_gm				(0b11<<RDA_SPACE_gp)
#define RDA_SPACE_100KHZ_gc			(0b00<<RDA_SPACE_gp)
#define RDA_SPACE_200KHZ_gc			(0b01<<RDA_SPACE_gp)
#define RDA_SPACE_50KHZ_gc			(0b10<<RDA_SPACE_gp)
#define RDA_SPACE_25KHZ_gc			(0b11<<RDA_SPACE_gp)

// CTRLB
#define RDA_INT_MODE_bm				(1<<15)
#define RDA_SEEKTH_gp				8
#define RDA_SEEKTH_gm				(0b1111<<RDA_SEEKTH_gp)
#define RDA_VOLUME_gp				0
#define RDA_VOLUME_gm				(0b1111<<RDA_VOLUME_gp)

// OPEN
#define RDA_OPEN_MODE_gp			13
#define RDA_OPEN_MODE_gm			(0b11<<RDA_OPEN_MODE_gp)
#define RDA_OPEN_MODE_OPEN_gc		(0b11<<RDA_OPEN_MODE_gp)
#define RDA_OPEN_MODE_CLOSED_gc		(0b00<<RDA_OPEN_MODE_gp)

// BAND
#define RDA_SEEK_TH_OLD_gp			2
#define RDA_SEEK_TH_OLD_gm			(0x3F<<RDA_SEEK_TH_OLD_gp)
#define RDA_FREQ_MODE_bm			(1<<0)

// STATUSA
#define RDA_RDSR_bm					(1<<15)
#define RDA_STC_bm					(1<<14)
#define RDA_SF_bm					(1<<13)
#define RDA_RDSS_bm					(1<<12)
#define RDA_BLK_E_bm				(1<<11)
#define RDA_ST_bm					(1<<10)
#define RDA_READCHAN_gp				0
#define RDA_READCHAN_gm				(0x1FF<<RDA_READCHAN_gp)

// STATUSB
#define	RDA_RSSI_gp					9
#define RDA_RSSI_gm					(0x3F<<RDA_RSSI_gp)
#define RDA_FM_TRUE_bm				(1<<8)
#define RDA_FM_READY_bm				(1<<7)
#define RDA_ABCD_E_bm				(1<<4)
#define RDA_BLERA_gp				2
#define RDA_BLERA_gm				(0b11<<RDA_BLERA_gp)
#define RDA_BLERB_gp				0
#define RDA_BLERB_gm				(0b11<<RDA_BLERA_gp)



extern void RDA_get_time(void);


#endif /* RDA5807M_H_ */
