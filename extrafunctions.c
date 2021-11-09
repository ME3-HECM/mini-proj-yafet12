/* 
 * File:   extra_functions.c
 * Author: yafet
 *
 * Created on 09 November 2021, 13:39
 */

#include <stdio.h>
#include <stdlib.h>
#include "comparator.h"
int leap_year_constant=0;
//this functions checks if the current year is a leap 
void Check_Leap_year(year_global) {
    
    if (year_global%4==0) {
        
        leap_year_constant = 1;
        if ((day_global==59) && (leap_year_constant==1)) {
            day_global-=1;
        }
    }
    else {leap_year_constant=0;}
            
}

void calibration(unsigned int hour) {
    
    if (hour==midnight_global) {
        
        T0CON0bits.T0EN=1;	//start the timer
    }
}
