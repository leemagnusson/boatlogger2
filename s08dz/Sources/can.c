
#include "can.h"
#include "flags.h"

byte can_rx_ptr = 0;
byte can_rx_data[CAN_RX_BUF_LEN];
extern enum Flags mainFlags;

void init_can()
{
	// set up can for 250 kbit/s using 4 MHz external clock
	// set up receive_isr for interrupt on receive
}


__interrupt VectorNumber_Vcanrx void receive_isr()
{
	byte data_length, i;
	// send data to receive buffer, increment pointer
	// set received flag
	
	data_length = CANRDLR_DLC + 4; // 4 bytes for id field
	for(i=0;i<data_length;i++) {
		can_rx_data[can_rx_ptr] = CANRDSR_ARR[i];
		//can_rx_ptr = cir_inc(can_rx_ptr);
	}
	can_rx_data[can_rx_ptr] = data_length; // also save the data length field, debugging only really
	//can_rx_ptr = cir_inc(can_rx_ptr);
	
	// send message to main()
	mainFlags |= F_CAN_RX;
	
	// clear interrupt flag
}



