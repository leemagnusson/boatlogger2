/*
 * serial.h
 *
 *  Created on: Sep 21, 2010
 *      Author: Lee
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include "derivative.h"

#define NEWLINE_AND_LINEFEED 1

void init_serial(void);
void putc1(byte c);
void puts1(byte *c, int length, byte);
int cir_inc(int i);
int putcint1(int c);
int cir_dec(int i);
void putcontrol1(byte b);

#endif /* SERIAL_H_ */
