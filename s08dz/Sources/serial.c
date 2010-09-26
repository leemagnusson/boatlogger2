

#include "serial.h"
//#include "can.h"
#include "derivative.h"
#include "rprintf.h"

#define SERIAL1_OUT_BUF_LEN		400

static byte serial1_out_buf[SERIAL1_OUT_BUF_LEN];
static int buf1_pos = 0;
static int buf1_end = -1;

void init_serial()
{
	SCI1BDL = 10;	
	SCI1C2_TE = 1; // enable transmitter output
	rprintf_devopen(putcint1);
}

int putcint1(int c)
{
	putc1((byte) c);
	return 0;
}

void putc1(byte c)
{
	puts1(&c,1);
}

// note this wouldn't work if there were nested calls (such as due to nested interrupts)
void puts1(byte *str, int length)
{
	byte i;
	int tmp_pos = buf1_end;
	// copy str to serial_out_buf, not greater than length
	for (i=0;i<length;i++) {
		tmp_pos = cir_inc(tmp_pos);
		serial1_out_buf[tmp_pos] = str[i];
	}
	// update the end_ptr, which is the point that the serial will output up to
	buf1_end = tmp_pos; 
	
	// enable the tx free interrupt, which should start the process 
	// immediately with tx_open_isr, if not already outputting
	SCI1C2_TIE = 1;
}

int cir_inc(int i)
{
	i++;
	if (i>=SERIAL1_OUT_BUF_LEN)
		i = 0;
	return i;
}

__interrupt VectorNumber_Vsci1tx void tx1_open_isr(void)
{
	if (SCI1S1_TDRE) {
		buf1_pos = cir_inc(buf1_pos);
		SCI1D = serial1_out_buf[buf1_pos];
	// transmit data until buf_pos gets up to buf_end

		if (buf1_pos == buf1_end) {
			// disable interrupt
			SCI1C2_TIE = 0;
		}
	}
	// clear flag
	
}

