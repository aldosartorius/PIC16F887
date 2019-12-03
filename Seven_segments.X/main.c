/*
 * File:   main.c
 * Author: Soul_PC
 *
 * Created on 9 de octubre de 2019, 10:58 AM
 * MISRA 12 verified on November 08, 2019
*/
/*                          ***********                                           */
/*                          *         * -->RC1 (Led 1) (7 segments)               */
/*           Catode(RA2) <--*         * -->RC2 (Led 2)                            */
/*                          *         * -->RC3 (Led 3)                            */
/*                          *         * -->RC3 (Led 3)                            */
/*                          *         * -->RC4 (Led 4)                            */
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
// CONFIG1

#pragma config WDTE = OFF              // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)

#include <xc.h>

//Function prototypes
int main(void);
void zero(void);
void one(void);
void two(void);
void three(void);
void four(void);
void five(void);
void six(void);
void seven(void);
void eight(void);
void nine(void);
void DP(void);
void Timer_Delay(void); 


int main(void) {
    
    //Oscillator Control Register (OSCCON)
    OSCCON = (unsigned char)0x15;      //Define internal oscilator, Fosc = 125 Khz
    
    //Analog Select Register (ANSEL)
    ANSEL &= (unsigned char)0x0;       //Disable  port A as analogic port (Energy saving, Port A enable darlington diodes for LCD)
    ANSELH &=(unsigned char)0x0;       //Disable  port B as analogic port (Energy saving, Port B Reads butoms)
    
    //Tri State Control Register (TRIS)
    TRISC = (unsigned char)0x0;        //All port C defined as output
    TRISAbits.TRISA2 = 0;              //Port A pin 2 as output (Activate Darlington Driver)
    PORTC &= (unsigned char)0x0;       //Clean port C
    PORTAbits.RA2 = 1;                 //Activate Seven segments Catode

    while(1){
        Timer_Delay();
        zero();
        Timer_Delay();
        one();
        Timer_Delay();
        two();
        Timer_Delay();
        three();
        Timer_Delay();
        four();
        Timer_Delay();
        five();  
        Timer_Delay();
        six();
        Timer_Delay();
        seven();
        Timer_Delay();
        eight();       
        Timer_Delay(); 
        nine();
    }
}
void zero(void){
    //PORTAbits.RA2 = 1;
    PORTC = (unsigned char)0x3F;        //Write zero in seven segments    
}
void one(void){
   // PORTAbits.RA2 = 1;
    PORTC = (unsigned char)0x06;        //Write one in seven segments  
}
void two(void){
  //  PORTAbits.RA2 = 1;
    PORTC = (unsigned char)0x5B;        //Write two in seven segments
}
void three(void){
   // PORTAbits.RA2 = 1;
    PORTC = (unsigned char)0x4F;        //Write three in seven segments 
}
void four(void){
  //  PORTAbits.RA2 = 1;
    PORTC = (unsigned char)0x66;        //Write four in seven segments  
}
void five(void){
   // PORTAbits.RA2 = 1;
    PORTC = (unsigned char)0x6D;        //Write five in seven segments 
}
void six(void){
  //  PORTAbits.RA2 = 1;
    PORTC = (unsigned char)0x7D;        //Write six in seven segments
}
void seven(void){
   // PORTAbits.RA2 = 1;
    PORTC = (unsigned char)0x07;        //Write seven in seven segments 
}
void eight(void){
   // PORTAbits.RA2 = 1;
    PORTC = (unsigned char)0x7F;        //Write eight in seven segments 
}
void nine(void){
   // PORTAbits.RA2 = 1;
    PORTC = (unsigned char)0x6F;        //Write nine in seven segments  
}

void DP(void){
   // PORTAbits.RA2 = 1;
    PORTC = (unsigned char)0x6F;       //Write point in seven segments    
}

void Timer_Delay(void){  //Two seconds delay
    
    //PIE1 REGISTER (Peripherical Interrupt Enable Register)
    PIE1 &= (unsigned char)0x1;        //Enable TMR1 Interrupt
   
    TMR1L = (unsigned char)0x18;       //Holding Register for the Least Significant Byte of the 16-bit TMR1 Register 
    TMR1H = (unsigned char)0x86;       //Holding Register for the Most Significant Byte of the 16-bit TMR1 Register 
    
    //Timer1 Control Register (T1CON)
    T1CON |= (unsigned char)0x1;       //Enable TMR1
    
    while(PIR1bits.TMR1IF == 0){};     //Wait until Timer1 Overflow Interrupt Flag bit (0 not overflow)
    PIR1bits.TMR1IF = 0;               //Clean Peripherical Interrupt Register 1 (TMR1 flag)  
}
