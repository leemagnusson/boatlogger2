
#include "can.h"
#include "flags.h"
#include "serial.h"
#include "error.h"
#include "rprintf.h"
#include "rtc.h"
#include "global_defines.h"
#include "string.h"

#include <stdlib.h>

//byte can_rx_ptr = 0;
//byte can_rx_data[CAN_RX_BUF_LEN];
//extern enum Flags mainFlags;


static byte source_address;
static byte name[ADDRESS_CLAIM_PGN_LENGTH] = "heyfool";

void init_can()
{
	// set up can for 250 kbit/s using 4 MHz external clock
	// set up receive_isr for interrupt on receive
	CANCTL1_CANE = 1;
	CANCTL0_INITRQ = 1;
	while(!CANCTL1_INITAK);
	
// can initialization mode writes
	CANCTL1_LOOPB = LOOPBACK_MODE;
	CANCTL1_LISTEN = LISTEN_ONLY_MODE;
	
	CANBTR0_SJW = 0b01;
	// frequency = 1/(tseg1+tseg2+3)
	CANBTR1_TSEG_20 = 5;
	CANBTR1_TSEG_10 = 8;
	
	/*// 8 8bit masks
	CANIDAC_IDAM = 0b10;	
	// set a mask to let in all possibilities
	CANIDMR0 = 0xFF;*/
	
	// set the masks
	// 4 16 bit masks
	CANIDAC_IDAM = 0b01;
	CANIDMR0 = HIGH_BYTE(MASK_ISO_PDU2);
	CANIDMR1 = LOW_BYTE(MASK_ISO_PDU2);
	CANIDMR2 = HIGH_BYTE(MASK_ISO_PDU1);
	CANIDMR3 = LOW_BYTE(MASK_ISO_PDU1);
	CANIDMR4 = HIGH_BYTE(MASK_NMEA_PDU2);
	CANIDMR5 = LOW_BYTE(MASK_NMEA_PDU2);
	CANIDMR6 = HIGH_BYTE(MASK_NMEA_PDU1);
	CANIDMR7 = LOW_BYTE(MASK_NMEA_PDU1);
	CANIDAR0 = HIGH_BYTE(FILT_ISO_PDU2);
	CANIDAR1 = LOW_BYTE(FILT_ISO_PDU2);
	CANIDAR2 = HIGH_BYTE(FILT_ISO_PDU1);
	CANIDAR3 = LOW_BYTE(FILT_ISO_PDU1);
	CANIDAR4 = HIGH_BYTE(FILT_NMEA_PDU2);
	CANIDAR5 = LOW_BYTE(FILT_NMEA_PDU2);
	CANIDAR6 = HIGH_BYTE(FILT_NMEA_PDU1);
	CANIDAR7 = LOW_BYTE(FILT_NMEA_PDU1);
	
	CANCTL0_INITRQ = 0;
	while(CANCTL1_INITAK);
	
// not initialization mode writes
	CANRIER_RXFIE = 1;
	
	srand(2);		//TODO initialize this with random ad values 
	generate_new_source_address();
	address_claim_message();
	
}

void generate_new_source_address()
{
	source_address = (byte) (rand()%0x7E)+0x80;
}

void address_claim_message()
{
	iso_m m;
	
	m.bits.priority = 6;
	ISO_M(ADDRESS_CLAIM_PGN);
	m.bits.data = name;
	transmit_iso(&m);
}

// mostly should be just used for testing unformatted messages
void transmit_can(dword *id, byte *data, byte length)
{
	byte i;
	
	do {
		CANTBSEL = CANTFLG;
	} while (CANTBSEL == 0);
	
	// 32 bit id register
	//CANTIDR0 = priority << 5 | blah;
	CANTIDR = *id;
	CANTIDR1 |= 0x18;		// set the srr and ide bits
	//memcpy(&CANTIDR0, data, length);
	for (i=0;i<length;i++) {
		CANTDSR_ARR[i] = data[i];
	}
	CANTDLR = length;
	
	// transmit the message
	CANTFLG = CANTBSEL;
}

void transmit_iso(iso_m *m)
{
//	byte i;
	
	do {
		CANTBSEL = CANTFLG;
	} while (CANTBSEL == 0);
	
/*	CANTIDR0 = m->priority<<5 | m->edp<<4 | m->dp<<3 | (m->pf)>>5;
	CANTIDR1 = 0x18 | (m->pf<<1 & 0x6) | (m->pf<<3 & 0xE0) | m->ps>>7;
	CANTIDR2 = m->ps<<1 | source_address>>7;
	CANTIDR3 = source_address<<1;		// note rtr bit is always 0 (data frame)*/
	
	m->bits.sa = source_address;
	CANTIDR = m->dw_id;
	
	/*for (i=0;i<m->bits.length;i++) {
		CANTDSR_ARR[i] = m->bits.data[i];
	} */
	_memcpy_8bitCount((void *)CANTDSR_ARR, m->bits.data, m->bits.length);
	CANTDLR = m->bits.length;
	
#if !LOOPBACK_MODE
	print_to_serial(&CANTIDR0);
#endif
	
#if !LISTEN_ONLY_MODE
	// transmit the message
	CANTFLG = CANTBSEL;
#endif
}

//#define HEX_OUT
__interrupt VectorNumber_Vcanrx void receive_isr()
{


#if !LOOPBACK_MODE
	// if address claim message and not loopback, process message
	switch (CANIDAC_IDHIT) {
	case ISO_PDU1_HIT: iso_pdu1_rx(&CANRIDR0); break;	//TODO fix this
	}
#endif
	
	
	print_to_serial(&CANRIDR0);
	
	// send message to main()
	//mainFlags |= F_CAN_RX;
	
	// clear interrupt flag
	CANRFLG_RXF = 1;
}

void print_to_serial(byte *can_buf)
{
	byte data_length;
#if ASCII_OUT
	byte i;
#endif;
	
	data_length = (can_buf[12]&0xF) + 4; // 4 bytes for id field
	
#if ASCII_OUT
	rprintf("%02X ", data_length);
	for(i=0;i<data_length;i++)
		rprintf("%02X ", can_buf[i]);
	rprintf("\n");
#else
	putc1(0xAB);
	putc1(0xCD);
	putc1(data_length);
	puts1(&can_buf, (int) data_length);		// from the id field forward through the bytes
#endif
}

void iso_pdu1_rx(iso_m *m_receive)
{
	iso_m m;
	byte i;
	
	// if address claim and this source address, then send out a new address claim
	if (m_receive->bits.sa == source_address) {
		// quick first check
		m.bits.priority = 6;
		ISO_M(ADDRESS_CLAIM_PGN);
		
		if (m_receive->dw_id == m.dw_id) {
			// if my name < received name I get to keep my source address
			for(i=0;i<ADDRESS_CLAIM_PGN_LENGTH;i++) {
				if (name[i] < m_receive->bits.data[i])
					break;
				if (name[i] > m_receive->bits.data[i]) {
					generate_new_source_address();
					break;
				}
				if (i == ADDRESS_CLAIM_PGN_LENGTH-1)
					generate_new_source_address();
			}
			address_claim_message();
		}
	}
}

