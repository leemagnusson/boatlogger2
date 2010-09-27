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
	byte i;
	struct IsoMessage m;
	union BatteryStatus bs; 
	
	for (i=0; i<AD_LENGTH; i++) {
#ifdef CAN_OUT
		bs.Bits.battery_instance = i;
		bs.Bits.voltage_V_01 = ad_raw_vals[i];
		bs.Bits.current_A_1 = ad_raw_vals[i];
		bs.Bits.temperature_K = 0;
		bs.Bits.sid = 0;
		m.data = bs.data;
		m.priority = 6;
		ISO_M(BATTERY_STATUS_PGN);
		transmit_iso(&m);
#else
	
#endif
	}
}
