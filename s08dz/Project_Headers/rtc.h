/*
 * rtc.h
 *
 *  Created on: Sep 12, 2010
 *      Author: Lee
 */

#ifndef RTC_H_
#define RTC_H_

void init_rtc(void);
void start_ms_timer(unsigned int *time);
unsigned int get_ms_timer(unsigned int time);



#endif /* RTC_H_ */
