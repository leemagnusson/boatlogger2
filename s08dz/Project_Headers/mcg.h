

#ifndef MCG_H
#define MCG_H

#define F_OSC	4000000
#define F_INT	32768		// approximately 
#define RDIV	2		// divide by 4 for PLL, 128 for FLL
#define BDIV	1		// default value divide by 2
#define BDIV_PLL 0		
#define VDIV	0b1001		// multiply by 32 for PLL
#define VDIV_VAL	36		
#define RDIV_32 0b111		// use when FLL is active

#define F_PEE	(F_OSC/(1<<RDIV))*(VDIV_VAL/(1<<BDIV_PLL))
#define F_FEI	F_INT*1024/BDIV			// should be about 16 MHz

#if F_PEE > 40000000
#error pee too fast
#elif F_FEI > 40000000
#error
#endif



enum Mode { FEI, FEE, FBI, FBE, BLPI, BLPE, PBE, PEE };

void init_mcg(void);
void pee(void);
void pbe(void);
void fbe(void);
void blpe(void);
void fei(void);
void blpi(void);
void fbi(void);
void fee(void);

#endif
