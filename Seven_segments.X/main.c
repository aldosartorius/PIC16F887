/*
 * File:   main.c
 * Author: Soul_PC
 *
 * Created on 9 de octubre de 2019, 10:58 AM
 */
//https://electronics.stackexchange.com/questions/171530/pic-microchip-keeps-resetting
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


void main(void) {
    
    
    OSCCON = 0x15;//  Define Fosc = 125 Khz
    ANSEL &= 0x0;        //Disable  port A as analogic port (Energy saving, Port A enable darlington diodes for LCD)
    ANSELH &=0x0;        //Disable  port B as analogic port (Energy saving, Port B Reads butoms)
    TRISC = 0x0;   //
    TRISAbits.TRISA2 = 0;
    PORTC &= 0x0;
     PORTAbits.RA2 = 1;

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
////      Timer_Delay();
    }
    
    return;
}
void zero(void){
    //PORTAbits.RA2 = 1;
    PORTC = 0x3F;   //Write zero in seven segmets    
}
void one(void){
   // PORTAbits.RA2 = 1;
    PORTC = 0x06;   //Write one in seven segmets  
}
void two(void){
  //  PORTAbits.RA2 = 1;
    PORTC = 0x5B;   //Write two in seven segmets 
}
void three(void){
   // PORTAbits.RA2 = 1;
    PORTC = 0x4F;   //Write three in seven segmets  
}
void four(void){
  //  PORTAbits.RA2 = 1;
    PORTC = 0x66;   //Write four in seven segmets  
}
void five(void){
   // PORTAbits.RA2 = 1;
    PORTC = 0x6D;   //Write five in seven segmets   
}
void six(void){
  //  PORTAbits.RA2 = 1;
    PORTC = 0x7D;   //Write six in seven segmets  
}

void seven(void){
   // PORTAbits.RA2 = 1;
    PORTC = 0x07;   //Write seven in seven segmets  
}
void eight(void){
   // PORTAbits.RA2 = 1;
    PORTC = 0x7F;   //Write eight in seven segmets   
}

void nine(void){
   // PORTAbits.RA2 = 1;
    PORTC = 0x6F;   //Write nine in seven segmets   
}

void DP(void){
   // PORTAbits.RA2 = 1;
    PORTC = 0x6F;   //Write point in seven segmets    
}

void Timer_Delay(void){  //Two seconds delay
    
    //PIE1 REGISTER (Peripherical Interrupt Enable Register)
    PIE1 &= 0x1;                   //Enable TMR1 Interrupt
    TMR1L = 0x18;                  //Preload charge data
    TMR1H = 0x86;                  //Preload charge data
    T1CON |= 0x1;                   //Enable TMR1
    while(PIR1bits.TMR1IF == 0);   //Wait until timer interrupt
    PIR1bits.TMR1IF = 0;           //Clean Peripherical Interrupt Register 1 (TMR1 flag)  
}
