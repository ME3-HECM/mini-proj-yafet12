#ifndef _comparator_H
#define _comparator_H

#include <xc.h>

#define _XTAL_FREQ 64000000

void DAC_init(void);
void Comp1_init(void);
void Check_Leap_year(int year_global);
void calibration(unsigned int hour);
void Reset_time(int day);
int Daily_offset(dusk_hour, dawn_hour);
extern int hour_global;
extern int day_global;
extern int year_global;
extern int midnight_global;   //for callibration
extern unsigned char leap_year;
#endif
