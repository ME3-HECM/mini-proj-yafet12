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
#include "extrafunctions.h"
#include <stdio.h>
#include <stdlib.h>

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  
/*
 * 
 */


void main(void) {
    
    LEDarray_init();            //initialise all the pins connected to the LED array
    LATHbits.LATH3=0;
    TRISHbits.TRISH3=0;

    Interrupts_init();  //initialise the enable registers of all the interrupts to be used
    DAC_init();         // don't worry about this for now
    Comp1_init();
    Timer0_init();      //this causes the loop to stop??
    
    calibration(hour);
    
    while (1) {
        
             //this function checks if the hour counter is between 1 and 5 to turn on the LED
        
        if (timer_overflow_flag && count_in_minutes%60==0) {
            
            hour++;                         //the hour counter increments when the minute counter reaches multiples of 60
            timer_overflow_flag=0;
        }
        
        if (count_in_minutes==24) {                    
            LEDarray_disp_bin(count_in_minutes);    //the hour still needs to be displayed
            day_global++;                           //increment day after 24 hours
            count_in_minutes=0;                                //reset the hour counter once hour reaches 24 hours
        }
        else {LEDarray_disp_bin(count_in_minutes);}
        
        night = Check_if_between_1and5(count_in_minutes);   //function checks if the time is between 1 and 5am.  
        
        
 
        Reset_time(day_global);        //this function will reset the hour counter everyday
        Check_Leap_year(year_global);               //this function will check if it is a leap year and make the corrections
    }
    
      
}

