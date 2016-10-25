/*
 * global.h
 *
 */ 


#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stdbool.h>

#define FALSE	0
#define TRUE	(!FALSE)


#define LE_CHR(a,b,c,d)		( ((uint32_t)(a)<<24) | ((uint32_t)(b)<<16) | ((c)<<8) | (d) )
#define WE_CHR(c,d)			( ((c)<<8) | (d) )

#define ARRAY_SIZE(a)		(sizeof(a) / sizeof(a[0]))


/**************************************************************************************************
* Fast binary to 2 digit decimal, only valid for 0-99
*/
static inline void clk_bin2dec(int8_t bin, uint8_t *dt, uint8_t *du)
{
	*du = 0;
	while ((bin -= 10) > 0)
		(*du)++;
	*dt = bin + 10;
}


/**************************************************************************************************
** Assembler macros
*/

#define NOP()	__asm__ __volatile__("nop")
#define	WDR()	__asm__ __volatile__("wdr")
/*
#define	WDR()	do {__asm__ __volatile__("wdr");			\
					VPORT1.OUT &= ~PIN0_bm;					\
					VPORT1.OUT |= PIN0_bm; } while(0);
*/


#endif /* GLOBAL_H_ */