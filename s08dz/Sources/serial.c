

#include "serial.h"
//#include "can.h"
#include "derivative.h"
#include "rprintf.h"

#define SERIAL1_OUT_BUF_LEN		400

static byte serial1_out_buf[SERIAL1_OUT_BUF_LEN];
static byte serial1_out_control[SERIAL1_OUT_BUF_LEN];
static int buf1_pos = 0;
static int buf1_end = -1;
static const byte HEX_MAP[] = "0123456789ABCDEF";
static byte serial1_control_buf[30];

extern byte ascii_out;

void init_serial()
{
	SCI1BDL = 10;	// baud rate = BUSCLK/this/16 -> 112,500 
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
	puts1(&c,1,0);
}

void putcontrol1(byte b)
{
	switch (b) {
	case NEWLINE_AND_LINEFEED:
		puts1("\r\n",2,1);
		break;
	}
}

// note this wouldn't work if there were nested calls (such as due to nested interrupts)
void puts1(byte *str, int length, byte control)
{
	byte i;
	int tmp_pos = buf1_end;
	// copy str to serial_out_buf, not greater than length
	for (i=0;i<length;i++) {
		tmp_pos = cir_inc(tmp_pos);
		serial1_out_buf[tmp_pos] = str[i];
		serial1_out_control[tmp_pos] = control;
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

int cir_dec(int i)
{
	i--;
	if (i<0)
		i = SERIAL1_OUT_BUF_LEN-1;
	return i;
}
__interrupt VectorNumber_Vsci1tx void tx1_open_isr(void)
{
	static byte nibble = 0;
	if (SCI1S1_TDRE) {
		buf1_pos = cir_inc(buf1_pos);
		
		if (ascii_out) {
			if (serial1_out_control[buf1_pos] == 1)
				SCI1D = serial1_out_buf[buf1_pos];
			else if (nibble == 0) {
				nibble = 1;
				SCI1D = HEX_MAP[(serial1_out_buf[buf1_pos]&0xF0)>>4];
				buf1_pos = cir_dec(buf1_pos);
			} else {
				nibble = 0;
				SCI1D = HEX_MAP[serial1_out_buf[buf1_pos]&0xF];		
			}
		} else {
			SCI1D = serial1_out_buf[buf1_pos];
		}
	// transmit data until buf_pos gets up to buf_end

		if (buf1_pos == buf1_end) {
			// disable interrupt
			SCI1C2_TIE = 0;
		}
	}
	// clear flag
	
}

