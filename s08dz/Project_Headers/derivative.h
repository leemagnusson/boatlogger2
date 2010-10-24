/*
 * Note: This file is recreated by the project wizard whenever the MCU is
 *       changed and should not be edited by hand
 */


#ifndef DERIVATIVE_H
#define DERIVATIVE_H

/* Include the derivative-specific header file */
#include <mc9s08dz60.h>
#include "global_defines.h"

#define HIGH_BYTE(x)		(x>>8)
#define LOW_BYTE(x)			(x&0xFF)
#define BYTE_SWAP(x)		(((x&0xFF)<<8) |(x&0xFF00)>>8)

typedef union fp {
	long l;
	struct parts {
		int h;
		int l;
	} i;
} FIXED16_16;
#define ROUND_FIXED16_16(x)		(x.l+=(long)0x8000, x.i.h)
#define FLOAT_TO_FIXED16_16(x) 	(long) (x*0x10000)

#define _Stop asm ( stop; )
  /*!< Macro to enter stop modes, STOPE bit in SOPT1 register must be set prior to executing this macro */

#define _Wait asm ( wait; )
  /*!< Macro to enter wait mode */

#endif

