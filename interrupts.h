#ifndef _interrupts_H
#define _interrupts_H

#include <xc.h>

#define _XTAL_FREQ 64000000

void Interrupts_init(void);

void __interrupt(high_priority) HighISR();

//the following variables must be declared with 'extern' so all other c files can read this
extern volatile unsigned int count_in_minutes;
extern volatile unsigned int hour;
extern int night;
unsigned int timer_overflow_flag;


#endif
