/*
 * adc.c
 *
 *  Created on: Sep 21, 2010
 *      Author: Lee
 */

#include "adc.h"
#include "rprintf.h"
#include "flags.h"

extern enum Flags mainFlags;


word ad_raw_vals[AD_LENGTH];


void init_adc()
{
	ADCCFG = 0b11000110; 		// low power, short conv, external 1 MHz clock
	APCTL1 = PTA_AD_VAL;
	APCTL2 = PTB_AD_VAL;
	APCTL3 = PTC_AD_VAL;
	ADCSC1_AIEN = 1;	// interrupt enable
	ADCSC2_ADTRG = 1; 		// conversion started by rtc
	ADCSC1_ADCH = AD_BEGIN;
	
}

interrupt VectorNumber_Vadc void adc_isr()
{
	static unsigned char ad_sel = AD_BEGIN;
	static unsigned char ad_avg_count = 0;
	static unsigned int ad_avg_val = 0;
	
	ADCSC2_ADTRG = 0;			// software trigger now
	
	ad_avg_val += ADCR;
	
	if (++ad_avg_count >= AD_AVG) {
		ad_avg_count = 0;
		//ad_convt_vals[ad_sel-AD_START] = ((long) 500 * (long) ad_avg_val)>>12;
		ad_raw_vals[ad_sel-AD_START] = ad_avg_val;
		ad_avg_val = 0;

		//adc_can_message(ad_sel, ad_convt_vals[])

	//	rprintf("ad%d: %d\n",ad_sel, ad_convt_vals[ad_sel-AD_START]);//ad_convt_vals[ad_sel]);

		ad_sel = next_ad_sel(ad_sel);
		if (ad_sel > AD_END) {
			ad_sel = AD_BEGIN;
			ADCSC2_ADTRG = 1; 		// conversion started by rtc
			mainFlags |= F_AD_DATA;
		}
		
		
		
	}

	ADCSC1_ADCH = ad_sel;
}

byte next_ad_sel(byte ad_sel) {
	do {
		++ad_sel;
	} while (!(AD_COLLECT_MASK & ((dword)1<<ad_sel)) && (ad_sel <= AD_END));
	return (ad_sel);
}

