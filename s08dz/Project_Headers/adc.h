/*
 * adc.h
 *
 *  Created on: Sep 21, 2010
 *      Author: Lee
 */

#ifndef ADC_H_
#define ADC_H_

#include "derivative.h"

#define AD_START	0
#define AD_END		27
#define AD_LENGTH  AD_END-AD_START+1

#define AD_AVG		8		// collect eight samples for every item box

#define PTC_AD_VAL	0b11011111
#define PTB_AD_VAL	0b11110111		// skip over some channels that are led outputs
#define PTA_AD_VAL	0b11111111

#define AD_COLLECT_MASK	 ((dword) (((dword)0b00011100<<24) | ((dword)PTC_AD_VAL<<16) | ((dword)PTB_AD_VAL<<8) | (dword)PTA_AD_VAL))

#define AD_BEGIN	0

void init_adc(void);
byte next_ad_sel(byte ad_sel);
void start_adc(void);

#endif /* ADC_H_ */
