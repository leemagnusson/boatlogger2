/*
 * io.c
 *
 *  Created on: May 1, 2011
 *      Author: Lee
 */

#include "derivative.h"
#include "io.h"
#include "led.h"

byte loopback_mode;
byte ascii_out;
byte take_measurements;

void init_io()
{
	int i;
	PTGDD &= ~0x3C;
	PTGPE |= 0x3C;
	for(i=0;i<50;i++); // necessary for the pull up to enable
	
	// dip1 off: loopback on
	// dip2 off: ascii on
	// dip3 off: report measurements on
	
	loopback_mode = PTGD_PTGD2; 
	ascii_out = PTGD_PTGD3;
	take_measurements = PTGD_PTGD4; // debug feature for not outputting any readings

	//loopback_mode = 0;
//	ascii_out = 1;
//	report_measurements = 1;
}
