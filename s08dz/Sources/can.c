
#include "can.h"
#include "flags.h"
#include "serial.h"

#include "rprintf.h"

//byte can_rx_ptr = 0;
//byte can_rx_data[CAN_RX_BUF_LEN];
//extern enum Flags mainFlags;

#define LOOPBACK_MODE		1		// 1=on, 0=off
#define LISTEN_ONLY_MODE	0		// 1=on, 0=off

static byte source_address = 0xAA;

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
	
	// 8 8bit masks
	CANIDAC_IDAM = 0b10;
	
	// set a mask to let in all possibilities
	CANIDMR0 = 0xFF;
	
	CANCTL0_INITRQ = 0;
	while(CANCTL1_INITAK);
	
// not initialization mode writes
	CANRIER_RXFIE = 1;
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

void transmit_iso(struct IsoMessage *m)
{
	byte i;
	
	do {
		CANTBSEL = CANTFLG;
	} while (CANTBSEL == 0);
	
	CANTIDR0 = m->priority<<5 | m->edp<<4 | m->dp<<3 | (m->pf)>>5;
	CANTIDR1 = 0x18 | (m->pf<<1 & 0x6) | (m->pf<<3 & 0xE0) | m->ps>>7;
	CANTIDR2 = m->ps<<1 | source_address>>7;
	CANTIDR3 = source_address<<1;		// note rtr bit is always 0 (data frame)
	
	for (i=0;i<m->length;i++) {
		CANTDSR_ARR[i] = m->data[i];
	}
	CANTDLR = m->length;
	
	// transmit the message
	CANTFLG = CANTBSEL;
}

#define HEX_OUT
__interrupt VectorNumber_Vcanrx void receive_isr()
{
	byte data_length;
#ifdef HEX_OUT
	byte i;
#endif
	
	data_length = CANRDLR_DLC + 4; // 4 bytes for id field

#ifdef HEX_OUT
	rprintf("%02X ", data_length);
	for(i=0;i<data_length;i++)
		rprintf("%02X ", CANRIDR_ARR[i]);
	rprintf("\n");
#else
	putc1(data_length);
	puts1(&CANRIDR0, (int) data_length);		// from the id field forward through the bytes
#endif
	
	// send message to main()
	//mainFlags |= F_CAN_RX;
	
	// clear interrupt flag
	CANRFLG_RXF = 1;
}



