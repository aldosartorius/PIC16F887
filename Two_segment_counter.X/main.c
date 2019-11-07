/*
 * File:   main.c
 * Author: Soul_PC
 *
 * Created on 9 de octubre de 2019, 10:58 AM
 */

// CONFIG1
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

void Timer_Delay(void); 

void main(void) {
    
    short units = 0;
    short tens = 0;
    short anti_blink = 0;
    short number[ ] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };
    
    ANSEL &= 0x0;        //Disable  port A as analogic port (Energy saving, Port A enable darlington diodes for LCD)
    ANSELH &=0x0;        //Disable  port B as analogic port (Energy saving, Port B Reads butoms)
    TRISC = 0x0;   //
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA3 = 0;
    PORTC &= 0x0;
    
     
     
    while(1){
    
        //Decenas
        PORTC= number[units];
        PORTAbits.RA3 = 1;     //Activate first segment
        for(short count = 0; count < 10; count++){
            Timer_Delay();     
        }
        PORTAbits.RA3 = 0;    //Desactivate first segment

        //Unidades
        PORTC = number[tens];
        PORTAbits.RA2 = 1;      //Activate second segment
        for(short count = 0; count < 10; count++){
            Timer_Delay();     
        }
        PORTAbits.RA2 = 0;      //Desactivate second segment

        anti_blink++;           //Anti blink delay
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

    return;
}

void Timer_Delay(void){  //Two seconds delay
    
    //PIE1 REGISTER (Peripherical Interrupt Enable Register)
    PIE1 &= 0x1;                   //Enable TMR1 Interrupt
    TMR1L = 0x90;                  //Preload charge data
    TMR1H = 0xFD;                  //Preload charge data
    T1CON |= 0x1;                   //Enable TMR1
    while(PIR1bits.TMR1IF == 0);   //Wait until timer interrupt
    PIR1bits.TMR1IF = 0;           //Clean Peripherical Interrupt Register 1 (TMR1 flag)  
}
