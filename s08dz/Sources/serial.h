/*
 * serial.h
 *
 *  Created on: Sep 21, 2010
 *      Author: Lee
 */

#ifndef SERIAL_H_
#define SERIAL_H_

void init_serial();

int put1(int c);

void rx_open_isr();

void update_end_ptr(unsigned char end_ptr);

#endif /* SERIAL_H_ */
