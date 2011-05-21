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

static unsigned int seconds = 0;
static void (*rtc_callbacks[1]) (void); // just one function for now
static byte rtc_callback_length = 0;

void init_rtc()
{
	RTCSC_RTCLKS = 0b01; 		// external clock ERCLK
	RTCSC_RTIE = 1;				// enable the interrupt
	//RTCSC_RTCPS = 0b1111;		// prescaler  2e5 i.e. .05s at 4 MHz clock
	//RTCMOD = 20;
	RTCSC_RTCPS = 0b1100;		//  5ms at 4 MHz clock
	RTCMOD = 200;
}

void start_ms_timer(unsigned int *time)
{
	*time = seconds*1000 + RTCCNT;
}

unsigned int get_ms_timer(unsigned int time)
{
	return (seconds*1000 + RTCCNT - time); // does this work up to 65535 ms?
}

void register_rtc_callback(void (*fun) (void))
{
	rtc_callbacks[rtc_callback_length++] = fun;
}

interrupt VectorNumber_Vrtc void rtc_isr()
{
	byte i;
//	toggle_led(LED1);
	seconds++;
//	rprintf("time since start: %d seconds\n",seconds++);
	
	// clear flag
	for (i=0;i<rtc_callback_length;i++)
		rtc_callbacks[i]();
	RTCSC_RTIF = 1;
}
