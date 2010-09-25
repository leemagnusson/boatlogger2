
#include "can.h"

byte can_rx_ptr = 0;
byte can_rx_data[CAN_RX_BUF_LEN];

void init_can()
{
	// set up can for 250 kbit/s using 4 MHz external clock
	// set up receive_isr for interrupt on receive
}

/*
void receive_isr()
{
	// send data to receive buffer, increment pointer
	// set received flag
	
	data_length = CAN_RX_FG_DL + 4; // 4 bytes for id field
	for(i=0;i<data_length;i++) {
		can_rx_data[can_rx_ptr] = CAN_RX_FG[i];
		cir_inc(can_rx_ptr);
	}
	can_rx_data[can_rx_ptr] = CAN_RX_FG_DL; // also save the data length field
	cir_inc(can_rx_ptr);
	
	// send message to main()
	MainFlags |= CAN_RX;
	
	// clear flag
}*/

byte cir_inc(byte *i)
{
	(*i)++;
	if (*i>CAN_RX_BUF_LEN)
		*i = 0;
	return *i;
}

