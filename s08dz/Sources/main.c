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

enum Flags mainFlags = 0;

void main(void) {
	unsigned int i;
  EnableInterrupts;
  SOPT1_COPT = 0; // no watchdog

  init_mcg();
  pee(); 		// note doesn't seem to work right in debug mode
  //pbe();
  init_serial();
  init_leds();
  init_rtc();
  init_adc();
  init_can();
  
  rprintf("123456789012345678901234567890");

  for(;;) {
    //__RESET_WATCHDOG();	/* feeds the dog */
    for(i=0;i<50000;i++);

	//  while(!mainFlags);		// waiting for something to happen, will sleep here
	  
	  toggle_led(LED2);
//	  if (mainFlags & F_CAN_RX) {
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
