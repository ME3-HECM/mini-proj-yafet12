/* 
 * File:   main.c
 * Author: yafet
 *
 * Created on 02 November 2021, 16:33
 */
#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)

// CONFIG3L
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include "LEDarray.h"
#include "interrupts.h"
#include "comparator.h"
#include "timers.h"
#include <stdio.h>
#include <stdlib.h>

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  
/*
 * 
 */

unsigned char night_time;  //introduce this variable to let us know whether it is between 1-5am (1) or not 0. automatically 0 at first
void main(void) {
    
    LEDarray_init();            //initialise all the pins connected to the LED array
    LATHbits.LATH3=0;
    TRISHbits.TRISH3=0;

    Interrupts_init();  //initialise the enable registers of all the interrupts to be used
    DAC_init();         // don't worry about this for now
    Comp1_init();
    Timer0_init();
    
    while (1) {
        
        if (count_in_minutes%60==0) {
            hour++;                         //the hour counter increments when the minute counter reaches multiples of 60
        }
        if (hour==24) {                    
            LEDarray_disp_bin(hour);
            hour=0;                                //reset the hour counter once hour reaches 24 hours
        }
        else {LEDarray_disp_bin(hour);}            //display the hour of the day on the LED
        
        LED_night_time_check(hour);     
        
    }
    
      
}

