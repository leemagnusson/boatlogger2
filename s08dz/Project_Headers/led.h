/*
 * led.h
 *
 *  Created on: Sep 12, 2010
 *      Author: Lee
 */

#ifndef LED_H
#define LED_H

//#define LED_ON_1 // Led turns on with a logic one to the port

#define LED_PORT(x)	PTC ## x
#define LED_PORT2(x) PTB ## x
#define LED1		1<<5
#define LED2		1<<3
#define ALL_LEDS	LED1 | LED2

typedef unsigned char LED_ID;

void init_leds(void);
void toggle_led(LED_ID);
void on_led(LED_ID);
void off_led(LED_ID);


#endif
