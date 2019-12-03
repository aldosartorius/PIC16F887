/*
 * File:   main.c
 * Author: Soul_PC
 *
 * Created on September 30, 2019, 12:34 PM
 * MISRA 12 verified on November 07, 2019
*/
/*                          ***********                                           */
/*                          *         * -->RC0 (Led 1)                            */
/*                          *         *                                           */
/*                          *         * -->RC2 (Led 2)                            */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
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

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


#include <xc.h>

//Function prototypes
int main(void);
void delay(void);  


int main(void) {
    
    //Oscillator Control Register (OSCCON)
    OSCCON = 0x71;                             //Define internal oscilator, 8 MHz

    //Analog Select Register (ANSEL)
    ANSEL &= (unsigned char)0x0;               //Disable  port A as analogic port (Energy saving, Port A enable darlington diodes for LCD)
    ANSELH &= (unsigned char)0x0;              //Disable  port B as analogic port (Energy saving, Port B Reads butoms)


    //Tri State Control Register (TRIS)
    TRISC &= (unsigned char)0x0;               //Define all C port as Output
    TRISE &= (unsigned char)0x0;               //Define all E port as Output (Port E activate Darlington Driver)

    PORTC &= (unsigned char)0x0;               //Clean port C
    PORTE &= (unsigned char)0b001;             //Write 0b001 in port E (activate A5 in Darlington diode)

    while(1){
        delay();
        PORTC = (unsigned char)0x1;            //Turn on Led 1 turn off led 2
        delay();
        PORTC = (unsigned char)0x4;            //Turn off Led 1 turn on led 2
        delay();
    }
}

void delay(void){
    int i,j;
    for  (i = 0; i < 2;  i++){
        for (j = 0; j < 10000;  j++) {};    
    }

}
