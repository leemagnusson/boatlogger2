/*
 * led.c
 *
 *  Created on: Sep 12, 2010
 *      Author: Lee
 */

#include "led.h"
#include "derivative.h"

void init_leds()
{
	LED_PORT(DD) = LED1;
	LED_PORT2(DD) = LED2;
	off_led(ALL_LEDS);
}

void toggle_led(LED_ID id)
{
	LED_PORT(D) ^= (id & LED1);
	LED_PORT2(D) ^= (id & LED2);
}

void on_led(LED_ID id)
{
#ifdef LED_ON_1
	LED_PORT(D) |= (id & LED1);
	LED_PORT2(D) |= (id & LED2);
#else
	LED_PORT(D) &= ~(id & LED1);
	LED_PORT2(D) &= ~(id & LED2);
#endif
}

void off_led(LED_ID id)
{
#ifdef LED_ON_1
	LED_PORT(D) &= ~(id & LED1);
	LED_PORT2(D) &= ~(id & LED2);
#else
	LED_PORT(D) |= (id & LED1);
	LED_PORT2(D) |= (id & LED2);
#endif
}

