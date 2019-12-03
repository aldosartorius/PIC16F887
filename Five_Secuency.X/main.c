/*
 * File:   main.c
 * Author: Soul_PC
 *
 * Created on 8 de octubre de 2019, 01:05 PM

 *  * MISRA 12 verified on November 08, 2019
*/
/*                          ***********                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
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
#pragma config WDTE = OFF  //WatchDog Off 

#include <xc.h>

//Function prototypes
int main(void);
void Timer_Delay(void); 
void Secuence_One(void);
void Secuence_Two(void);
void Secuence_Three(void);
void Secuence_Four(void);
void Secuence_Five(void);


int main(void) {
    
     //Oscillator Control Register (OSCCON)
    OSCCON = 0x15;                      //Define internal oscilator, Fosc = 125 Khz

    //Analog Select Register (ANSEL)
    ANSEL &= (unsigned char)0x0;        //Disable port A as analogic port (Energy saving, Port A enable darlington diodes for LCD)
    ANSELH &=(unsigned char)0x0;        //Disable port B as analogic port (Energy saving, Port B Reads butoms)

     //Tri State Control Register (TRIS)
    TRISC &= (unsigned char)0x0;        //All port C defined as output
    TRISE &= (unsigned char)0x0;        //all E port as Output (Port E activate Darlington Driver)

    PORTC &= (unsigned char)0x0;        //Clean port C
    PORTE &= (unsigned char)0B001;      //Write 0b001 in port E (activate A5 in Darlington diode)
    
    while(1){
        
        Secuence_One();
        Secuence_Two();
        Secuence_Three();
        Secuence_Four();
        Secuence_Five();
    }
}

void Timer_Delay(void){  //Two seconds delay
    
    //PIE1 REGISTER (Peripherical Interrupt Enable Register)
    PIE1 &= (unsigned char)0x1;          //Enable TMR1 Interrupt
    
    TMR1L = (unsigned char)0x18;         //Holding Register for the Least Significant Byte of the 16-bit TMR1 Register 
    TMR1H = (unsigned char)0x86;         //Holding Register for the Most Significant Byte of the 16-bit TMR1 Register 
    
    //Timer1 Control Register (T1CON)
    T1CON |= (unsigned char)0x1;         //Enable TMR1
    
    while(PIR1bits.TMR1IF == 0){};       //Wait until Timer1 Overflow Interrupt Flag bit (0 not overflow)
    PIR1bits.TMR1IF = 0;                 //Clean Peripherical Interrupt Register 1 (TMR1 flag)  
}

void Secuence_One(void){ 
    
    PORTC = (unsigned char)0xF8;
    Timer_Delay();
    PORTC = (unsigned char)0x0;
    Timer_Delay();   
}

void Secuence_Two(void){ 
    
    PORTC = (unsigned char)0x80;
    Timer_Delay();
    PORTC = (unsigned char)0xC0;
    Timer_Delay();
    PORTC = (unsigned char)0xE0;
    Timer_Delay();
    PORTC = (unsigned char)0xF0;
    Timer_Delay();
    PORTC = (unsigned char)0xF8;
    Timer_Delay();
    PORTC = (unsigned char)0x78;
    Timer_Delay();
    PORTC = (unsigned char)0x38;
    Timer_Delay();
    PORTC = (unsigned char)0x18;
    Timer_Delay();
    PORTC = (unsigned char)0x8;
    Timer_Delay();
    PORTC = (unsigned char)0x00;
    Timer_Delay();
}

void Secuence_Three(void){ 
    
    PORTC = (unsigned char)0x0;
    Timer_Delay();
    PORTC = (unsigned char)0x88;
    Timer_Delay();
    PORTC = (unsigned char)0xD8;
    Timer_Delay();
    PORTC = (unsigned char)0xF8;
    Timer_Delay();
    PORTC = (unsigned char)0xD8;
    Timer_Delay();
    PORTC = (unsigned char)0x88;
    Timer_Delay();
    PORTC = (unsigned char)0x0;
    Timer_Delay();
}

void Secuence_Four(void){ 
    
    PORTC = (unsigned char)0x80;
    Timer_Delay();
    PORTC = (unsigned char)0x40;
    Timer_Delay();
    PORTC = (unsigned char)0x20;
    Timer_Delay();
    PORTC = (unsigned char)0x10;
    Timer_Delay();
    PORTC = (unsigned char)0x8;
    Timer_Delay();
    PORTC = (unsigned char)0x10;
    Timer_Delay();
    PORTC = (unsigned char)0x20;
    Timer_Delay();
    PORTC = (unsigned char)0x40;
    Timer_Delay();
    PORTC = (unsigned char)0x80;
    Timer_Delay();
}

void Secuence_Five(void){ 
    
    PORTC = (unsigned char)0xA8;
    Timer_Delay();
    PORTC = (unsigned char)0x50;
    Timer_Delay();
    PORTC = (unsigned char)0xF8;
    Timer_Delay();
    PORTC = (unsigned char)0x50;
    Timer_Delay();
    PORTC = (unsigned char)0xA8;
    Timer_Delay();    
}