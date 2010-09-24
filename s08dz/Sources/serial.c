

#include "serial.h"
//#include "can.h"
#include "derivative.h"
#include "rprintf.h"

//extern unsigned char can_rx_data[CAN_RX_BUF_LEN];

static unsigned char buf_pos_ptr = 0;
static unsigned char buf_end_ptr = 0;

void init_serial()
{
	SCI1BDL = 10;	
	SCI1C2_TE = 1; // enable transmitter output
	rprintf_devopen(put1);
}

int put1(int c)
{
	while(!SCI1S1_TDRE);
	return (SCI1D = (char) c);
}

void rx_open_isr()
{
	// transmit data until buf_pos_ptr gets up to buf_end_ptr
	if (buf_end_ptr != buf_pos_ptr) {
		// there is data to output
	//	txbuf = can_rx_data[buf_pos_ptr];
	//	cir_inc(buf_pos_ptr);
	}
	
	// clear flag
}

void update_end_ptr(unsigned char end_ptr)
{
	buf_end_ptr = end_ptr;
	// start outputting data if txbuf is open
//	if (txbufopen)
		rx_open_isr();
}
