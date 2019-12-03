/*
 * File:   newmain.c
 * Author: Soul_PC
 *
 * Created on 3 de octubre de 2019, 10:30 AM
 * MISRA 12 verified on November 08, 2019
*/
/*                          ***********                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         * -->RC5 (Led 5)                            */
/*                          *         * -->RC6 (Led 6)                            */
/*                          *         * -->RC7 (Led 7)                            */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         * --> RE0 UL2803A (Darlington diode)        */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          ***********                                           */


//https://electronics.stackexchange.com/questions/171530/pic-microchip-keeps-resetting
#pragma config WDTE = OFF  //WatchDog Off 


#include <xc.h>

//Function prototypes
int main(void);
void Timer_Delay(void);  

int main(void) {
        
    //Oscillator Control Register (OSCCON)
    OSCCON = 0x01;                                 //Define internal oscilator, Fosc = 31 Khz

    //Analog Select Register (ANSEL)
    ANSEL &= (unsigned char)0x0;                   //Disable  port A as analogic port (Energy saving, Port A enable darlington diodes for LCD)
    ANSELH &=(unsigned char)0x0;                   //Disable  port B as analogic port (Energy saving, Port B Reads butoms)


    //Tri State Control Register (TRIS)
    TRISC &= (unsigned char)0x0;                   //Define all C port as Output
    TRISE &= (unsigned char)0x0;                   //Define all E port as Output (Port E activate Darlington Driver)

    PORTC &= (unsigned char)0x0;                   //Clean port C
    PORTE &= (unsigned char)0b001;                 //Write 0b001 in port E (activate A5 in Darlington diode)
     
    PIR1bits.TMR1IF = 0;                          //Clean Peripherical Interrupt Register 1 (TMR1 flag)
   
    while(1){
        
        PORTC = (unsigned char)0x80;              //Turn on Led 7 & turn off leds 6 & 5
        Timer_Delay();
        Timer_Delay();
        PORTC = (unsigned char)0x40;             //Turn on Led 6 & turn off leds 7 & 5
        Timer_Delay();
        PORTC = (unsigned char)0x20;             //Turn on Led 5 & turn off leds 7 & 6
        Timer_Delay();
        Timer_Delay();
    }
}

void Timer_Delay(void){ //5 seconds
    
    //PIE1 REGISTER (Peripherical Interrupt Enable Register)
    PIE1bits.TMR1IE = 1;                         //Enable Timer1 Interrupt  
 
    
    TMR1L =(unsigned char)0x51;                  //Holding Register for the Least Significant Byte of the 16-bit TMR1 Register 
    TMR1H =(unsigned char)0xB4;                  //Holding Register for the Most Significant Byte of the 16-bit TMR1 Register 
    
    //Timer1 Control Register (T1CON)
    T1CON &= (unsigned char)0x18;                //Configure Timer1 as Internal Clock, 1:2 Prescaler
    T1CONbits.TMR1ON =1;                         //Timer1 enable bit
    
    //PIR1 REGISTER (Peripherical Interrupt Flag Register)
    while(PIR1bits.TMR1IF == 0){};               //Wait until Timer1 Overflow Interrupt Flag bit (0 not overflow)
    PIR1bits.TMR1IF = 0;                         //Clean Peripherical Interrupt Register 1 (TMR1 flag)   
}
