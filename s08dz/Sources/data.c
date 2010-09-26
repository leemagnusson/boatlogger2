/*
 * data.c
 *
 *  Created on: Sep 26, 2010
 *      Author: Lee
 */

// This file will process the data logging, stored in global variables throughout the program

#include "derivative.h"
#include "data.h"
#include "adc.h"
#include "can.h"
#include "rprintf.h"

#define CAN_OUT

extern int ad_raw_vals[AD_LENGTH];

void data_process()
{
	byte id[4] = "a8b";
	byte i;
	
	for (i=0; i<AD_LENGTH; i++) {
#ifdef CAN_OUT
	transmit_can(id, &ad_raw_vals[i],2);
#else
	
#endif
	}
}
