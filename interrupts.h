#ifndef _interrupts_H
#define _interrupts_H

#include <xc.h>

#define _XTAL_FREQ 64000000

void Interrupts_init(void);
//void __interrupt(high_priority) HighISR();
void __interrupt(high_priority) HighISR2();
void __interrupt(low_priority) LowISR();

//the following variables must be declared with 'extern' so all other c files can read this
extern volatile unsigned int count;
extern unsigned int hour;
unsigned char night_time;

#endif
