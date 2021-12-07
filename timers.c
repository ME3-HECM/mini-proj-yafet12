#include <xc.h>
#include "timers.h"

/************************************
 * Function to set up timer 0
************************************/
void Timer0_init(void)
{
    T0CON1bits.T0CS=0b010; // Fosc/4
    T0CON1bits.T0ASYNC=1; // see datasheet errata - needed to ensure correct operation when Fosc/4 used as clock source
    //T0CON1bits.T0CKPS=0b1111; // 1:32768
    //for testing purposes, 
    T0CON1bits.T0CKPS=0b0111;  //we want our prescaler to be 16384 as its closest to 14648 which is the value needed for the interval to be 1 minute long
    //we applied the offset a few lines down by setting the initial low and high registers different to 0.
    T0CON0bits.T016BIT=1;	//16bit mode. if set to 0 it goes into 8 bit mode	
	
    // it's a good idea to initialise the timer registers so we know we are at 0
    TMR0H=0b00011011;            //write High reg first, update happens when low reg is written to
    TMR0L=0b00011101;             
    //this number is 6941 which is the calculated offset needed so that overflow occurs every 60 seconds 
    
}

/************************************
 * Function to return the full 16bit timer value
 * Note TMR0L and TMR0H must be read in the correct order, or TMR0H will not contain the correct value
************************************/
unsigned int disp_val;
unsigned int get16bitTMR0val(void)
{
    disp_val = TMR0L;       //read from the low register first
    disp_val |= TMR0H<<8;   //then shift the high register to the correct position as most significant bits and read them
    
    return disp_val;
    
	//add your code to get the full 16 bit timer value here
}
