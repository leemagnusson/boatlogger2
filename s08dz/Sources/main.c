// $HeadURL$
// $Author$
// $Date$

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

#include "rtc.h"
#include "led.h"
#include "mcg.h"
#include "serial.h"
#include "rprintf.h"
#include "adc.h"
#include "flags.h"
#include "can.h"
#include "data.h"
#include "timer.h"
#include "io.h"

enum Flags mainFlags = 0;
extern byte take_measurements;

void main(void) {
	unsigned int i;
	byte id[4] = "q8z";
	byte data[8] = "testcan";
  EnableInterrupts;
  SOPT1_COPT = 0; // no watchdog
  
  i = 280 * id[0]; 

  init_mcg();
#ifdef SIMULATOR		
  pbe();
#else
  pee(); 		// note doesn't seem to work right in simulator mode
#endif
  init_leds();
  init_io();
  init_timers();
  init_serial();
  init_rtc();
  puts1("\x01\x23\x45\x67\x89\xab\xcd\xef",8,0);	
  putcontrol1(NEWLINE_AND_LINEFEED);
  init_adc();
  init_can();

  
 
  
  //rprintf("123456789012345678901234567890");
  
 // transmit_can(id, data, 8);

  for(;;) {
    //__RESET_WATCHDOG();	/* feeds the dog */
   // for(i=0;i<50000;i++);

	  while(!mainFlags); // _Wait;		// waiting for something to happen, will sleep here
	  toggle_led(LED2);
	  if (mainFlags & F_AD_DATA) {
		  if(take_measurements)
			  data_process();
		  mainFlags &= ~F_AD_DATA;
	  }
	//	  update_end_ptr();		// serial function
//	  }
    
    
  } /* loop forever */
  /* please make sure that you never leave main */
}

/*
struct char_div_t {
	char quot;
	char rem;
};

void char_div_16_8(struct char_div_t *, int dividend, char divisor);

#pragma MESSAGE DISABLE C5703 
void char_div_16_8(struct char_div_t *t, int dividend, char divisor)
{
	// dividend on H:X, divisor in A
	asm {
		PSHA;
		TXA;
		PULX;
		DIV;
	}
	// result of div is H remainder, A is quotient
	asm {
		PSHH;
		LDHX t;
		STA ,X;
		PULA;
		STA	1,X;
	}
	
}*/
