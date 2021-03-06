/*
 * data.c
 *
 *  Created on: Sep 26, 2010
 *      Author: Lee
 */

// This file will process the data logging, stored in global variables throughout the program


#include "data.h"
#include "adc.h"
#include "can.h"
#include "rprintf.h"


extern word ad_raw_vals[AD_LENGTH];


// matrix of ad_sel values and associated conversions for voltage
static const struct voltage_meas V_meas[] = {
		{20, &conv[CONV_CV_IND]}, 
		{21, &conv[CONV_CV_IND]},
		{22, &conv[CONV_CV_IND]}
	};
#define V_MEAS_LEN		sizeof V_meas / sizeof V_meas[0]
static int voltages[V_MEAS_LEN];


// matrix of ad_sel values and associated conversions for current
#define DEFAULT_C_OFFSET	4096/2*8
static const struct current_meas C_meas[] = {
		{0, &conv[CONV_DA_IND], DEFAULT_C_OFFSET}, 
		{1, &conv[CONV_DA_IND], DEFAULT_C_OFFSET},
		{2, &conv[CONV_DA_IND], DEFAULT_C_OFFSET},
		{3, &conv[CONV_DA_IND], DEFAULT_C_OFFSET}, 
		{4, &conv[CONV_DA_IND], DEFAULT_C_OFFSET},
		{5, &conv[CONV_DA_IND], DEFAULT_C_OFFSET},
		{6, &conv[CONV_DA_IND], DEFAULT_C_OFFSET}, 
		{7, &conv[CONV_DA_IND], DEFAULT_C_OFFSET},
		{8, &conv[CONV_DA_IND], DEFAULT_C_OFFSET},
		{9, &conv[CONV_DA_IND], DEFAULT_C_OFFSET}, 
		{10, &conv[CONV_DA_IND], DEFAULT_C_OFFSET}, 
		{11, &conv[CONV_DA_IND], DEFAULT_C_OFFSET},
		{12, &conv[CONV_DA_IND], DEFAULT_C_OFFSET},
		{13, &conv[CONV_DA_IND], DEFAULT_C_OFFSET}, 
		{14, &conv[CONV_DA_IND], DEFAULT_C_OFFSET},
		{15, &conv[CONV_DA_IND], DEFAULT_C_OFFSET},
		{16, &conv[CONV_DA_IND], DEFAULT_C_OFFSET}, 
		{17, &conv[CONV_DA_IND], DEFAULT_C_OFFSET},
		{18, &conv[CONV_DA_IND], DEFAULT_C_OFFSET},
		{19, &conv[CONV_DA_IND], DEFAULT_C_OFFSET}
	};
#define C_MEAS_LEN		sizeof C_meas / sizeof C_meas[0]
static int currents[C_MEAS_LEN];


// linking matrix of current associated with voltage
static const struct power_st powers[] = {
		{&voltages[2], &currents[0]},
		{&voltages[2], &currents[1]},
		{&voltages[2], &currents[2]},
		{&voltages[2], &currents[3]},
		{&voltages[2], &currents[4]},
		{&voltages[2], &currents[5]},
		{&voltages[2], &currents[6]},
		{&voltages[2], &currents[7]},
		{&voltages[2], &currents[8]},
		{&voltages[2], &currents[9]},
		{&voltages[2], &currents[10]},
		{&voltages[2], &currents[11]},
		{&voltages[2], &currents[12]},
		{&voltages[2], &currents[13]},
		{&voltages[2], &currents[14]},
		{&voltages[2], &currents[15]},
		{&voltages[2], &currents[16]},
		{&voltages[2], &currents[17]},
		{&voltages[2], &currents[18]},
		{&voltages[2], &currents[19]}
};
#define POWER_LEN		sizeof powers / sizeof powers[0]


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
	long l1, l2, l3;
	FIXED16_16 fp;
	for (i=0;i<V_MEAS_LEN;i++) {
		l1 = (long) ((int) ad_raw_vals[C_meas[i].ad_sel] - C_meas[i].offset);
		l2 = l1 * *(C_meas[i].conv)+0x8000;
		//l3 = HIGH_WORD(l2);
		fp.l = (long) ((int) (ad_raw_vals[C_meas[i].ad_sel] - C_meas[i].offset));
		fp.l *= *C_meas[i].conv;
		currents[i] = ROUND_FIXED16_16(fp);
		//currents[i] = (int)(((long) ((int) ad_raw_vals[C_meas[i].ad_sel] - C_meas[i].offset) * *(C_meas[i].conv))/((long)0x10000));
		//currents[i] = l3;//HIGH_WORD((long) ((int) ad_raw_vals[C_meas[i].ad_sel] - C_meas[i].offset) * *(C_meas[i].conv));
	}
}

void output_power_messages()
{
	byte i;
	iso_m m;
	union BatteryStatus bs; 
	
	for (i=0; i<3; i++) { //i<POWER_LEN; i++) {
#ifdef CAN_OUT
		bs.Bits.battery_instance = i+1;
		bs.Bits.voltage_V_01 = BYTE_SWAP(*powers[i].voltage);
		bs.Bits.current_A_1 = BYTE_SWAP(*powers[i].current);
		bs.Bits.temperature_K = 0xFFFF;
		bs.Bits.sid = 0xFF;
		m.bits.data = bs.data;
		m.bits.priority = 6;
		ISO_M(BATTERY_STATUS_PGN);
		transmit_iso(&m);
#else
	
#endif
	}
}
