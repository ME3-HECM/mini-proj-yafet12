#include <xc.h>
#include "LEDarray.h"

/************************************
/ LEDarray_init
/ Function used to initialise pins to drive the LEDarray
************************************/
void LEDarray_init(void)
{
    TRISGbits.TRISG0 = 0;
    TRISGbits.TRISG1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISFbits.TRISF6 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISFbits.TRISF0 = 0;
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;

    //we want all LEDs to be off initially
    LATGbits.LATG0 = 0;
    LATGbits.LATG1 = 0;
    LATAbits.LATA2 = 0;
    LATFbits.LATF6 = 0;
    LATAbits.LATA4 = 0;
    LATAbits.LATA5 = 0;
    LATFbits.LATF0 = 0;
    LATBbits.LATB0 = 0;
    LATBbits.LATB1 = 0;
 
    	//set up TRIS registers for pins connected to LED array
	//set initial output LAT values (they may have random values when powered on)
}

/************************************
/ LEDarray_disp_bin
/ Function used to display a number on the LED array in binary
************************************/
void LEDarray_disp_bin(unsigned int number)
{
    if (number & 0b000000001) {LATGbits.LATG0 = 1;} else {LATGbits.LATG0 = 0;}
    if (number & 0b000000010) {LATGbits.LATG1 = 1;} else {LATGbits.LATG1 = 0;}
    if (number & 0b000000100) {LATAbits.LATA2 = 1;} else {LATAbits.LATA2 = 0;}
    if (number & 0b000001000) {LATFbits.LATF6 = 1;} else {LATFbits.LATF6 = 0;}
    if (number & 0b000010000) {LATAbits.LATA4 = 1;} else {LATAbits.LATA4 = 0;}
    if (number & 0b000100000) {LATAbits.LATA5 = 1;} else {LATAbits.LATA5 = 0;}
    if (number & 0b001000000) {LATFbits.LATF0 = 1;} else {LATFbits.LATF0 = 0;}
    if (number & 0b010000000) {LATBbits.LATB0 = 1;} else {LATBbits.LATB0 = 0;}
    if (number & 0b100000000) {LATBbits.LATB1 = 1;} else {LATBbits.LATB1 = 0;}
    
    __delay_ms(50);    //delay so that change can be seen
}
 
	


   
//this function controls whether the LED is on or off during the hours (1am-5am)
void LED_night_time_check(unsigned int hour) 
{
    
    if (1<=hour<=5) {
        LATHbits.LATH3=1;  //LED turns on between (1-5am) 
    }
    else {
        LATHbits.LATH3=0;   //else LED is off
    }
}