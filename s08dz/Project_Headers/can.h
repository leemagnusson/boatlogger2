/*
 * can.h
 *
 *  Created on: Sep 25, 2010
 *      Author: Lee
 */

#ifndef CAN_H_
#define CAN_H_

#include "derivative.h"

void init_can(void);
void transmit_can(dword *, byte *, byte);

#endif /* CAN_H_ */
