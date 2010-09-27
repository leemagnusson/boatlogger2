/*
 * can.h
 *
 *  Created on: Sep 25, 2010
 *      Author: Lee
 */

#ifndef CAN_H_
#define CAN_H_

#include "derivative.h"

#define BATTERY_STATUS_PGN		127508
#define BATTERY_STATUS_PGN_LENGTH	8

#define EDP(x)					0
#define DP(x)					(x & 0x10000)>>16
#define ispdu1(x)				!(x & 0x8000)				// pdu1 is address based
#define PF(x)					(x & 0xFF00)>>8
#define DA						0
#define PS(x)					ispdu1(x) ? DA : x & 0xFF

#define ISO_M(x)				m.edp = EDP(x), m.dp = DP(x), m.pf = PF(x), m.ps = PS(x), m.length = x##_LENGTH

struct IsoMessage {
	byte priority : 3;		// note could try a union here
	byte edp : 1;
	byte dp : 1;
	byte : 0;
	byte pf;
	byte ps;
//	word pgn;
	byte *data;
	byte length;
};

union BatteryStatus {
	byte data[8];
	
	// no guarantee that this will be in the right order
	struct {
		byte battery_instance;
		int voltage_V_01;
		int current_A_1;
		int temperature_K;
		byte sid;
	} Bits;
};

void init_can(void);
void transmit_can(dword *, byte *, byte);
void transmit_iso(struct IsoMessage *m);

#endif /* CAN_H_ */
