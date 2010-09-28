/*
 * adc.h
 *
 *  Created on: Sep 21, 2010
 *      Author: Lee
 */

#ifndef ADC_H_
#define ADC_H_

#define AD_START	0
#define AD_END		15
#define AD_LENGTH  AD_END-AD_START+1

#define AD_AVG		8		// collect ten samples for every item box

#define PTC_AD_VAL	0b00000000
#define PTB_AD_VAL	0b11110000		// skip over some channels that are led outputs, but still read them
#define PTA_AD_VAL	0b11111111

void init_adc(void);

#endif /* ADC_H_ */
