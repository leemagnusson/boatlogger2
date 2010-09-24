/*
 * adc.c
 *
 *  Created on: Sep 21, 2010
 *      Author: Lee
 */

#include "adc.h"
#include "rprintf.h"
#include "derivative.h"


#define AD_START	0
#define AD_END		15
#define AD_LENGTH  AD_END-AD_START+1

#define AD_AVG		10		// collect ten samples for every item box

#define PTB_AD_VAL	0b11110000
#define PTA_AD_VAL	0b11111111

int ad_convt_vals[AD_LENGTH];


void init_adc()
{
	ADCCFG = 0b11000110; 		// low power, short conv, external 1 MHz clock
	APCTL1 = PTA_AD_VAL;
	APCTL2 = PTB_AD_VAL;
	ADCSC1_AIEN = 1;	// interrupt enable
	ADCSC2_ADTRG = 1; 		// conversion started by rtc
	ADCSC1_ADCH = AD_START;
	
}

interrupt 23 void adc_isr()
{
	static unsigned char ad_sel = AD_START;
	static unsigned char ad_avg_count = 0;
	static unsigned int ad_avg_val = 0;
	
	ADCSC2_ADTRG = 0;			// software trigger now
	
	ad_avg_val += ADCR;
	
	if (++ad_avg_count >= AD_AVG) {
		ad_avg_count = 0;
		ad_convt_vals[ad_sel-AD_START] = ((long) 500 * (long) ad_avg_val)>>12;
		ad_avg_val = 0;
		
		rprintf("ad%d: %d\n",ad_sel, ad_convt_vals[ad_sel-AD_START]);//ad_convt_vals[ad_sel]);
		if (++ad_sel > AD_END) {
			ad_sel = AD_START;
			ADCSC2_ADTRG = 1; 		// conversion started by rtc
		}
	}

	ADCSC1_ADCH = ad_sel;
}
