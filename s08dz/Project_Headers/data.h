/*
 * data.h
 *
 *  Created on: Sep 26, 2010
 *      Author: Lee
 */

#ifndef DATA_H_
#define DATA_H_

#include "derivative.h"

// voltage reference defines with conversions
#define AD_REF_SEL		23
#define V_REF			3.0//(5<<16)			// <<16 converts to Q16.16
#define V_REF_CV		FLOAT_TO_FIXED16_16(4*V_REF*100)		// convert counts to centivolts, format for conversions will be Q16.16, 4x factor due to voltage divider
#define V_REF_DA		FLOAT_TO_FIXED16_16(V_REF/100*10000*10)		// counts to deciamps, 100 mV/A -> now to centiamps with extra *10
#define CONV_LEN		2

#define CONV_CV_IND		0
#define CONV_DA_IND		1

static long conv[CONV_LEN] = {0,0};
static const long conv_ref[CONV_LEN] = {V_REF_CV, V_REF_DA};


// structs for voltage, current and power measurements
struct voltage_meas {
	byte ad_sel;
	long* conv;
};
struct current_meas {
	byte ad_sel;
	long* conv;
	int offset;
};
struct power_st {
	int* voltage;
	int* current;
};


void data_process(void);
void calc_conversions(void);
void calc_voltages(void);
void calc_currents(void);
void output_power_messages(void);

#endif /* DATA_H_ */
