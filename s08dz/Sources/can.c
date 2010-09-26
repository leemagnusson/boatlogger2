
#include "can.h"
#include "flags.h"
#include "serial.h"

//byte can_rx_ptr = 0;
//byte can_rx_data[CAN_RX_BUF_LEN];
//extern enum Flags mainFlags;

#define LOOPBACK_MODE		1		// 1=on, 0=off
#define LISTEN_ONLY_MODE	0		// 1=on, 0=off

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

void transmit_can(dword *id, byte *data, byte length)
{
	byte i;
	
	CANTBSEL = CANTFLG;
	
	// 32 bit id register
	//CANTIDR0 = priority << 5 | blah;
	CANTIDR = *id;
	//memcpy(&CANTIDR0, data, length);
	for (i=0;i<length;i++) {
		CANTDSR_ARR[i] = data[i];
	}
	CANTDLR = length;
	
	// transmit the message
	CANTFLG = CANTBSEL;
}


__interrupt VectorNumber_Vcanrx void receive_isr()
{
	int data_length;
	// send data to receive buffer, increment pointer
	// set received flag
	
	data_length = CANRDLR_DLC + 4; // 4 bytes for id field
	
	puts1(&CANRIDR0, data_length);		// from the id field forward through the bytes
	putc1((byte) data_length);
	
	/*for(i=0;i<data_length;i++) {
		can_rx_data[can_rx_ptr] = CANRDSR_ARR[i];
		//can_rx_ptr = cir_inc(can_rx_ptr);
	}*/
	/*can_rx_data[can_rx_ptr] = data_length; // also save the data length field, debugging only really*/
	//can_rx_ptr = cir_inc(can_rx_ptr);
	
	// send message to main()
	//mainFlags |= F_CAN_RX;
	
	// clear interrupt flag
	CANRFLG_RXF = 1;
}



