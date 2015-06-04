/*
 * can.h
 *
 *  Created on: Sep 25, 2010
 *      Author: Lee
 */

#ifndef CAN_H_
#define CAN_H_

#include "derivative.h"

#define BATTERY_STATUS_PGN			127508
#define BATTERY_STATUS_PGN_LENGTH	8
#define MAX_ADDRESS_TRIES			32

#define WIND_STATUS_PGN			130306
#define WIND_STATUS_PGN_LENGTH	6

#define ADDRESS_CLAIM_PGN			60928
#define ADDRESS_CLAIM_PGN_LENGTH	8

#define PRODUCT_INFORMATION_PGN		126996

#define DC_DETAILED_STATUS_PGN		127506

#define ISO_REQUEST_PGN				59904

#define EDP(x)					0
#define DP(x)					((x & 0x10000)>>16)
#define ispdu1(x)				((x & 0xF000) < 0xF000)				// pdu1 is address based
#define PF(x)					((x & 0xFF00)>>8)
#define PF1(x)					(PF(x)>>2)
#define PF2(x)					(PF(x)&3)
#define DA						0xFF
#define PS(x)					(ispdu1(x) ? DA : x & 0xFF)
#define PS1(x)					(PS(x)>>7)
#define PS2(x)					(PS(x)&0x7F)

#define ISO_M(x)				m.bits.edp = EDP(x), m.bits.dp = DP(x), m.bits.pf1 = PF1(x), \
								m.bits.pf2 = PF2(x), m.bits.ps1 = PS1(x), m.bits.ps2 = PS2(x), \
								m.bits.length = x##_LENGTH, \
								m.bits.srr = 1, m.bits.ide = 1, m.bits.rtr = 0
/*typedef union {
	dword dw_id;
	byte id[4];
	
	struct IsoMessage {
		dword priority : 3;		// note could try a union here
		dword edp : 1;
		dword dp : 1;
	//	byte : 0;
		dword pf1 : 6;
		dword srr : 1;
		dword ide : 1;
		dword pf2 : 2;
		dword ps : 8;
		dword sa : 8;
		dword rtr: 1;
	//	word pgn;
		byte *data;
		byte length;
	} bits ;
} iso_m; */

typedef union {
	dword dw_id;
	byte id[4];
	
	struct IsoMessage {
		word ps1 : 1;
		word pf2 : 2;
		word ide : 1;
		word srr : 1;
		word pf1 : 6;
		word dp : 1;
		word edp : 1;
		word priority : 3;		// note could try a union here
		
		
	//	byte : 0;	
		word rtr: 1;
		word sa : 8;
		word ps2 : 7;
		
		
	//	word pgn;
	//byte data[8];
		byte *data;
		byte length;
	} bits ;
} iso_m;

typedef union {
	dword dw_pgn;
	byte byte_pgn[4];
} pgn;

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

union WindStatus {
	byte data[6];
	
	// no guarantee that this will be in the right order
	struct {
		byte sid;
		int windspeed;
		int winddir;
		byte ref;
	} fields;
};
// these are 16 bit masks and acceptance filters, want to split between PDU1 and PDU2
// ISO appears to be only on DP 0, so use that as only criteria
// Everything that is an extended identifier is accepted by something, could remove that criteria too

#define MASK_ISO_PDU2	0xE067
#define FILT_ISO_PDU2	0x0798
// note, must fall through to pdu1 filter
#define MASK_ISO_PDU1	0xE7E7
#define FILT_ISO_PDU1	0x0018

#define MASK_NMEA_PDU2	0xE067
#define FILT_NMEA_PDU2	0x0F98
// note, must fall through to pdu1 filter
#define MASK_NMEA_PDU1	0xE7E7
#define	FILT_NMEA_PDU1	0x0818
enum {ISO_PDU2_HIT, ISO_PDU1_HIT, NMEA_PDU2_HIT, NMEA_PDU1_HIT};


void init_can(void);
void transmit_can(dword *, byte *, byte);
void transmit_iso(iso_m *m);
void address_claim(void);
void address_claim_message(void);
void print_to_serial(byte *can_buf);
void iso_pdu1_rx(iso_m *m_receive);
void generate_new_source_address(void);

#endif /* CAN_H_ */
