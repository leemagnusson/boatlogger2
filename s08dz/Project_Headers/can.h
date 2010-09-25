/*
 * can.h
 *
 *  Created on: Sep 25, 2010
 *      Author: Lee
 */

#ifndef CAN_H_
#define CAN_H_

#define CAN_RX_BUF_LEN		10*13		// 13 byte length per packet at most

#include "derivative.h"

void init_can(void);
byte cir_inc(byte i);

#endif /* CAN_H_ */
