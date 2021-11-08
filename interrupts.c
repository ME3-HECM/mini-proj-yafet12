#include <xc.h>
#include "interrupts.h"

/************************************
 * Function to turn on interrupts and set if priority is used
 * Note you also need to enable peripheral interrupts in the INTCON register to use CM1IE.
************************************/


unsigned char night_time;  //introduce this variable to let us know whether it is between 1-5am (1) or not 0
volatile unsigned int count;
unsigned int hour;

//function that initialise interrupt registers and turns on global registers
void Interrupts_init(void)
{
    //PIE0bits.INT0IE=1; //enable interrupt source INT0 
    PIE0bits.TMR0IE=1;  //this enables the register which are flags to say which interrupt was triggered
    PIE2bits.C1IE=1;
    INTCONbits.IPEN=0; //this value set to 0 disables the priorities of interrupts
    INTCONbits.PEIE=1;
    INTCONbits.GIE=1;
    
	// turn on global interrupts, peripheral interrupts and the interrupt source 
	// It's a good idea to turn on global interrupts last, once all other interrupt configuration is done.
}

/************************************
 * High priority interrupt service routine
 * Make sure all enabled interrupts are checked and flags cleared
************************************/

void __interrupt(low_priority) LowISR()       //this interrupt flag checks if the threshold voltage is reached
                                                //in response the IRS will turn on an LED
{
    if (PIR2bits.C1IF) {            //this checks if the flag PIR2bits.C1IF was triggered. if this value changes to 1 
        LATHbits.LATH3=1; //this is the action we want to perform if this flag is triggered which is turn on LED
        PIR2bits.C1IF=0;    // this clears the flag,i.e resets it back to 0 so it can be triggered again in future.
        
    }
	//add your ISR code here i.e. check the flag, do something (i.e. toggle an LED), clear the flag...
}
 

void __interrupt(high_priority) HighISR2()  //this interrupt flag is for the timer overflow so that we can track the time in minutes
{   
   
    if (PIR0bits.TMR0IF) {
        
        count++;
        TMR0H=0b00011011;            //write High reg first, update happens when low reg is written to
        TMR0L=0b00011101;
                     
        PIR0bits.TMR0IF=0;      //reset the flag that triggers the ISR 
    }
}
void __interrupt(high_priority) HighISR3()
{
    if (night_time) {

        LATHbits.LATH3=!LATHbits.LATH3;  //toggle this light so when it is night time (1-5am) then light comes on initially it's off
        night_time=0;
    }
}



