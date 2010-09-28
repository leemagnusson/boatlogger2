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

#define AD_REF_SEL		15
#define V_REF			(5*65536)//(5<<16)			// <<16 converts to Q16.16
#define V_REF_CV		V_REF*100		// convert counts to centivolts, format for conversions will be Q16.16
#define V_REF_DA		V_REF/131*10000		// counts to deciamps, 131 mV/A
#define CONV_LEN		2

#define CONV_CV_IND		0
#define CONV_DA_IND		1

static long conv[CONV_LEN] = {0,0};
static const long conv_ref[CONV_LEN] = {V_REF_CV, V_REF_DA};

struct voltage_meas {
	byte ad_sel;
	long* conv;
};

// matrix of ad_sel values and associated conversions for voltage
#define V_MEAS_LEN		2
static const struct voltage_meas V_meas[V_MEAS_LEN] = {
		{0, &conv[CONV_CV_IND]}, 
		{12, &conv[CONV_CV_IND]}
	};
static int voltages[V_MEAS_LEN];

struct current_meas {
	byte ad_sel;
	long* conv;
	int offset;
};
#define DEFAULT_C_OFFSET	4096/2*8
// matrix of ad_sel values and associated conversions for current
#define C_MEAS_LEN		2
static const struct current_meas C_meas[C_MEAS_LEN] = {
		{2, &conv[CONV_DA_IND], DEFAULT_C_OFFSET}, 
		{13, &conv[CONV_DA_IND], DEFAULT_C_OFFSET}
	};
static int currents[C_MEAS_LEN];

struct power_st {
	int* voltage;
	int* current;
};

// linking matrix of current associated with voltage
#define POWER_LEN		1
static const struct power_st powers[POWER_LEN] = {
		{&voltages[1], &currents[1]},
//		{&voltages[1], &currents[1]}
};

void data_process()
{
	calc_conversions();
	calc_voltages();
	calc_currents();
	output_power_messages();
}

void calc_conversions()
{
	byte i;
	for (i=0; i<CONV_LEN; i++) {
		conv[i] = conv_ref[i]/(long) ad_raw_vals[AD_REF_SEL];//
	}
	
}

void calc_voltages()
{
	byte i;
	for (i=0;i<V_MEAS_LEN;i++) {
		voltages[i] = (int)(((long) ad_raw_vals[V_meas[i].ad_sel] * *V_meas[i].conv)>>16);
	}
}

void calc_currents()
{
	byte i;
	for (i=0;i<V_MEAS_LEN;i++) {
		currents[i] = (int)(((long) (ad_raw_vals[C_meas[i].ad_sel] - C_meas[i].offset) * *C_meas[i].conv)>>16);
	}
}

void output_power_messages()
{
	byte i;
	struct IsoMessage m;
	union BatteryStatus bs; 
	
	for (i=0; i<POWER_LEN; i++) {
#ifdef CAN_OUT
		bs.Bits.battery_instance = i+1;
		bs.Bits.voltage_V_01 = *powers[i].voltage;
		bs.Bits.current_A_1 = *powers[i].current;
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
