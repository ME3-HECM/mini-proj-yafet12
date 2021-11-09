#include <xc.h>
#include "interrupts.h"

/************************************
 * Function to turn on interrupts and set if priority is used
 * Note you also need to enable peripheral interrupts in the INTCON register to use CM1IE.
************************************/

int night=0;
unsigned int timer_overflow_flag;
volatile unsigned int count_in_minutes;
volatile unsigned int hour=0;

//function that initialise interrupt registers and turns on global registers
void Interrupts_init(void)
{
    
    PIE0bits.TMR0IE=1;  //this enables the timer0 interrupt 
    PIE2bits.C1IE=1;    //this enables the comparator interrupt (the LDR signal reader)
    INTCONbits.IPEN=0; //this value set to 0 disables the priorities of interrupts
    INTCONbits.PEIE=1;
    INTCONbits.GIE=1;   //this is turns on global interrupts
    
	// turn on global interrupts, peripheral interrupts and the interrupt source 
	// It's a good idea to turn on global interrupts last, once all other interrupt configuration is done.
}

/************************************
 * High priority interrupt service routine
 * Make sure all enabled interrupts are checked and flags cleared
************************************/


void __interrupt(high_priority) HighISR()  //this interrupt flag is for the timer overflow so that we can track the time in minutes
{   
   
    if (PIR0bits.TMR0IF) {
        
        count_in_minutes++;             //this is the ISR, so every time the timer overflows (every minute) the minute counter increases
        timer_overflow_flag=1;
        TMR0H=0b00011011;            //write High reg first, update happens when low reg is written to
        TMR0L=0b00011101;           
        //this is the offset needed so that the interrupt flag is set off every minute
                    
        PIR0bits.TMR0IF=0;      //reset the flag that triggers the ISR 
    }       
    
    if (PIR2bits.C1IF) {           //this checks if the LDR voltage changes past the threshold which in turn changes the output value of the pin. 
        if (!CM1CON0bits.OUT){      //this is the comparator output if it is a 1, it means there was a change from night to day. 
            
            LATHbits.LATH3=0;
            PIR2bits.C1IF=0;
        }
        else if (CM1CON0bits.OUT) {    //this is the comparator output if it is a 0, it means there was a change from day to night.
            
            if (!night)
            {
                LATHbits.LATH3=1;
            }
            PIR2bits.C1IF=0;
            
        }
        
            // this clears the flag,i.e resets it back to 0 so it can be triggered again in future.
       
    }
    
}     


//for some reason creating two interrupt functions created an error but including the 2 ISRs in one function worked???

