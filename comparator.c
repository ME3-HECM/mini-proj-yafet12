#include <xc.h>
#include "comparator.h"

int leap_year_constant=0;   //this is used later to check if it is a leap year
int hour_global;
int day_global;
int year_global=1;
int midnight_global=0;   //for callibration
unsigned char leap_year;

/************************************
 * Function to set up DAC for use by the comparator module
************************************/
void DAC_init(void)
{
    DAC1CON0bits.PSS=0b00;      //3.3V for positive source (Vdd)
    DAC1CON0bits.NSS=0b0;      //0v for Negative source (Vss))
	//5-bit DAC value to set output voltage
    // min is 0 = 0V
    // max is 2^5-1 = 31 = 3.3V
    DAC1CON1bits.DAC1R=0b10100; // adjust according to ambient light 2.7~2.87V
    DAC1CON0bits.DAC1EN=1;      //turn on DAC
}

/************************************
 * Function to set up comparator to compare RF7 to the DAC output voltage
 * Note the CM1 interrupt is not enabled by this function 
************************************/
void Comp1_init(void)
{
    TRISFbits.TRISF7=1;		// set pin RF7 as input
    CM1NCHbits.NCH=0b011; 	// pin RF7 as input for comparator
    CM1PCHbits.PCH=0b101;   //use DAC output for positive input
    CM1CON0bits.HYS=1;      //a little bit of hysteresis to stop multiple triggers
    CM1CON0bits.POL=1;      //needed for interrupt to work
    CM1CON1bits.INTP=1; 	//set interrupt flag on positive going edge
    CM1CON1bits.INTN=1; 	//set interrupt flag on negative going edge
    DAC_init();				//initialise the DAC
    CM1CON0bits.EN=1;   	//enable comparator 1
}


void Reset_time(int day) {
    
    if (day==365) {
        
        year_global++;
        day_global=0;
    }

}


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