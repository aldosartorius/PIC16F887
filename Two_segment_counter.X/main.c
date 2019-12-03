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
/*           Catode(RA3) <--*         * -->RC3 (Led 3)                            */
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

// CONFIG1

#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)

#include <xc.h>

//Function prototypes
int main(void);
void Timer_Delay(void); 

int main(void) {
    
    short units = 0;
    short tens = 0;
    short anti_blink = 0;
    short number[ ] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };
    
    //Analog Select Register (ANSEL)
    ANSEL &= (unsigned char)0x0;       //Disable  port A as analogic port (Energy saving, Port A enable darlington diodes for LCD)
    ANSELH &= (unsigned char)0x0;      //Disable  port B as analogic port (Energy saving, Port B Reads butoms)
    
    //Tri State Control Register (TRIS)
    TRISC = (unsigned char)0x0;        //All port C defined as output
    TRISAbits.TRISA2 = 0;              //Port A pin 2 as output (Activate Darlington Driver)
    TRISAbits.TRISA3 = 0;              //Port A pin 3 as output (Activate Darlington Driver)
    PORTC &= (unsigned char)0x0;       //Clean port C
         
    while(1){
    
        //Decenas
        PORTC= (unsigned char)number[units];
        PORTAbits.RA3 = 1;             //Activate first segment
        for(short count = 0; count < 10; count++){
            Timer_Delay();     
        }
        PORTAbits.RA3 = 0;             //Desactivate first segment

        //Unidades
        PORTC = (unsigned char)number[tens];
        PORTAbits.RA2 = 1;             //Activate second segment
        for(short count = 0; count < 10; count++){
            Timer_Delay();     
        }
        PORTAbits.RA2 = 0;             //Desactivate second segment

        anti_blink++;                  //Anti blink delay
        if(anti_blink>20) {
            anti_blink=0;
           units++;               
        }
            
        if(units > 9){
            units = 0;
            tens++;
            if(tens >9){
                 tens = 0;
            }
        }
       }
}

void Timer_Delay(void){  //Two seconds delay
    
    //PIE1 REGISTER (Peripherical Interrupt Enable Register)
    PIE1 &= (unsigned char)0x1;        //Enable TMR1 Interrupt
    
    TMR1L = (unsigned char)0x90;       //Holding Register for the Least Significant Byte of the 16-bit TMR1 Register
    TMR1H = (unsigned char)0xFD;       //Holding Register for the Most Significant Byte of the 16-bit TMR1 Register 
   
    //Timer1 Control Register (T1CON)
    T1CON |= (unsigned char)0x1;       //Enable TMR1
    while(PIR1bits.TMR1IF == 0){};       //Wait until Timer1 Overflow Interrupt Flag bit (0 not overflow)
    PIR1bits.TMR1IF = 0;               //Clean Peripherical Interrupt Register 1 (TMR1 flag)  
}
