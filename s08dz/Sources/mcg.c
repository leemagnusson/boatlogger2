

#include "mcg.h"
#include "derivative.h"

static Mode = FEI;

void init_mcg()
{
	// set timing defaults, other functions shouldn't change the div values
	MCGC1 = RDIV_32<<3 | 0x04; // CLKS = %00, RDIV = %???, IREFS = 1, IRCLKEN = 0, IREFSTEN = 0
	MCGC2 = BDIV<<6 | 0x36; // BDIV = %??, RANGE = 1, HGO = 1, LP = 0, EREFS = 1, ERCLKEN = 1, EREFSTEN = 0
	MCGC3 = VDIV | 0x10; // LOLIE = 0, PLLS = 0, CME = 0, DIV32 = 1, VDIV = %????
	//  note div32 does not appear to work 
	
	while(!MCGSC_OSCINIT);				// waiting for OSCINIT == 1
}

void pee()
{
	switch (Mode) {
		case PEE: return; 
		case PBE: break;
		default: pbe(); break;
	}
	// mode here should be PBE
	// CLKS %10->%00
	while(!(MCGSC_LOCK)); 				// waiting for LOCK == 1
	
	MCGC1_CLKS = 0b11;					// output of PLL selected
	while(MCGC1_CLKS != 0b11);			// waiting for CLKST == %11
	
	MCGC2_BDIV = BDIV_PLL;
	
	Mode = PEE;
}

void pbe()
{
	MCGC2_BDIV = BDIV; // switch back to divide by 2
	
	switch (Mode) {
		case PBE: return; 
		case PEE: break;
		case BLPE: // LP 1->0
			MCGC2_LP = 0;
			break;
		case FBE: break;
		default: fbe(); break;
	}
	// mode here should be FBE or PEE
	// PLLS 0->1, CLKS == %10
	
	MCGC1_RDIV = RDIV;
	MCGC3_PLLS = 1;
	MCGC1_CLKS = 0b10;					// external clock selected
	
	while(!(MCGSC_PLLST));				// waiting for PLLST == 1
	while(MCGSC_CLKST != 0b10); 		// waiting for CLKST == %10
	
	Mode = PBE;
}

void fbe()
{
	switch (Mode) {
		case FBE: return;
		case BLPI: fbi(); break;		// switch to FBI 
		case PEE: pbe(); break;			
		default: break; 
	}
	// IREFS 1->0, CLKS %00->%10, PLLS ->0, LP ->0
		
	MCGC1_RDIV = RDIV_32;
	MCGC1_IREFS = 0;
	MCGC1_CLKS = 0b10;
	MCGC3_PLLS = 0;
	MCGC2_LP = 0;
	
	while(MCGSC_PLLST);					// waiting for PLLS == 0;
	while(MCGSC_IREFST);				// waiting for IREFST == 0
	while(MCGSC_CLKST != 0b10); 		// waiting for CLKST == %10
	
	Mode = FBE;
}

void blpe()
{
	switch (Mode) {
		case BLPE: return;
		case PEE: pbe();
		case PBE:
		case FBE: break;
		default: fbe(); break;
	}
	// LP -> 1
	
	MCGC2_LP = 1;
	
	Mode = BLPE;
}

void fbi()
{
	switch (Mode) {
		case FBI: return;
		case PEE:
		case PBE:
		case BLPE: fbe(); break;
		default: break;
	}
	// IREFS ->1, CLKS = %01
	
	MCGC1_IREFS = 0;
	MCGC1_CLKS = 0b01;
	
	while(MCGSC_IREFST);				// waiting for IREFST == 0
	while(MCGSC_CLKST != 0b01); 		// waiting for CLKST == %10
	
	Mode = FBI;
}

void fei()
{
	switch (Mode) {
		case FEI: return;
		case BLPI: fbi(); break;
		case BLPE:
		case PBE:
		case PEE: fbe();
		default: break;
	}
	// IREFS ->1, CLKS ->%00
	
	while(!(MCGSC_LOCK)); 				// waiting for LOCK == 1
	
	MCGC1_IREFS = 1;
	MCGC1_CLKS = 0b00;
	
	while(!MCGSC_IREFST);				// waiting for IREFST == 1
	while(MCGSC_CLKST != 0b00); 		// waiting for CLKST == %00
	
	Mode = FEI;
}

void fee()
{
	switch (Mode) {
		case FEE: return;
		case BLPI: fbi(); break;
		case BLPE:
		case PBE:
		case PEE: fbe();
		default: break;
	}
	// IREFS ->0, CLKS ->%00
	
	while(!(MCGSC_LOCK)); 				// waiting for LOCK == 1
	
	MCGC1_IREFS = 0;
	MCGC1_CLKS = 0b00;
	
	while(MCGSC_IREFST);				// waiting for IREFST == 0
	while(MCGSC_CLKST != 0b00); 		// waiting for CLKST == %00
	
	Mode = FEE;
}

void blpi()
{
	switch (Mode) {
		case BLPI: return;
		case FBI: break;
		default: fbi();
	}
	// LP ->1
	
	MCGC2_LP = 1;
	
	Mode = BLPI;
}
