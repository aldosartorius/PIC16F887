/*
 * File:   main.c
 * Author: Soul_PC
 *
 * Created on 8 de octubre de 2019, 01:05 PM
 */

//https://electronics.stackexchange.com/questions/171530/pic-microchip-keeps-resetting
#pragma config WDTE = OFF  //WatchDog Off 
#include <xc.h>


void Timer_Delay(void); 
void Secuence_One(void);
void Secuence_Two(void);
void Secuence_Three(void);
void Secuence_Four(void);
void Secuence_Five(void);


void main(void) {
    
     OSCCON = 0x15;//  Define Fosc = 125 Khz

    ANSEL &= 0x0;        //Disable  port A as analogic port (Energy saving, Port A enable darlington diodes for LCD)
    ANSELH &=0x0;        //Disable  port B as analogic port (Energy saving, Port B Reads butoms)

    TRISC &= 0x0;          //All port C defined as output
    TRISE &= 0x0;        //all E port as Output (Port E activate Darlington Driver)
    
    PORTC &= 0x0;        //Clean port C
    PORTE &= 0B001;      //Write 0b001 in port E (activate A5 in Darlington diode)
    
    while(1){
        
        Secuence_One();
        Secuence_Two();
        Secuence_Three();
        Secuence_Four();
        Secuence_Five();
    }
    return;
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

void Secuence_One(void){ 
    
    PORTC = 0xF8;
    Timer_Delay();
    PORTC = 0x0;
    Timer_Delay();
    
}

void Secuence_Two(void){ 
    
    PORTC = 0x80;
    Timer_Delay();
    PORTC = 0xC0;
    Timer_Delay();
    PORTC = 0xE0;
    Timer_Delay();
    PORTC = 0xF0;
    Timer_Delay();
    PORTC = 0xF8;
    Timer_Delay();
    PORTC = 0x78;
    Timer_Delay();
    PORTC = 0x38;
    Timer_Delay();
    PORTC = 0x18;
    Timer_Delay();
    PORTC = 0x8;
    Timer_Delay();
    PORTC = 0x00;
    Timer_Delay();
}

void Secuence_Three(void){ 
    
    PORTC = 0x0;
    Timer_Delay();
    PORTC = 0x88;
    Timer_Delay();
    PORTC = 0xD8;
    Timer_Delay();
    PORTC = 0xF8;
    Timer_Delay();
    PORTC = 0xD8;
    Timer_Delay();
    PORTC = 0x88;
    Timer_Delay();
    PORTC = 0x0;
    Timer_Delay();
}

void Secuence_Four(void){ 
    
    PORTC = 0x80;
    Timer_Delay();
    PORTC = 0x40;
    Timer_Delay();
    PORTC = 0x20;
    Timer_Delay();
    PORTC = 0x10;
    Timer_Delay();
    PORTC = 0x8;
    Timer_Delay();
    PORTC = 0x10;
    Timer_Delay();
    PORTC = 0x20;
    Timer_Delay();
    PORTC = 0x40;
    Timer_Delay();
    PORTC = 0x80;
    Timer_Delay();
}

void Secuence_Five(void){ 
    
    PORTC = 0xA8;
    Timer_Delay();
    PORTC = 0x50;
    Timer_Delay();
    PORTC = 0xF8;
    Timer_Delay();
    PORTC = 0x50;
    Timer_Delay();
    PORTC = 0xA8;
    Timer_Delay();
     
}