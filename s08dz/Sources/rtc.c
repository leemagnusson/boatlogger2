/*
 * rtc.c
 *
 *  Created on: Sep 12, 2010
 *      Author: Lee
 */

#include "rtc.h"
#include "led.h"
#include "derivative.h"
#include "rprintf.h"

#define RTC_VEC		25

void init_rtc()
{
	RTCSC_RTCLKS = 0b01; 		// external clock ERCLK
	RTCSC_RTIE = 1;				// enable the interrupt
	RTCSC_RTCPS = 0b1111;		// prescaler  2e5 i.e. .05s at 4 MHz clock
	RTCMOD = 20;
}


interrupt RTC_VEC void rtc_isr()
{
	static int seconds = 0;
	toggle_led(LED1);
	rprintf("time since start: %d seconds\n",seconds++);
	
	// clear flag
	RTCSC_RTIF = 1;
}
