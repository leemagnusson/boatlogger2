/*
 * serial.h
 *
 *  Created on: Sep 21, 2010
 *      Author: Lee
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include "derivative.h"

void init_serial(void);
void putc1(byte c);
void puts1(byte *c, int length);
int cir_inc(int i);
int putcint1(int c);


#endif /* SERIAL_H_ */
