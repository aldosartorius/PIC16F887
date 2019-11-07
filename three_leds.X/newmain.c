/*
 * File:   newmain.c
 * Author: Soul_PC
 *
 * Created on 3 de octubre de 2019, 10:30 AM
 */

//https://electronics.stackexchange.com/questions/171530/pic-microchip-keeps-resetting
#pragma config WDTE = OFF  //WatchDog Off 


#include <xc.h>
#include<stdio.h>

void Timer_Delay(void);  

void main(void) {
        
    OSCCON = 0x01;//  000; //Define Fosc = 31 Khz

    ANSEL &= 0x0;        //Disable  port A as analogic port (Energy saving, Port A enable darlington diodes for LCD)
    ANSELH &=0x0;        //Disable  port B as analogic port (Energy saving, Port B Reads butoms)


    //Tri state control register
    TRISC &= 0x0;        //all C port as Output
    TRISE &= 0x0;        //all E port as Output (Port E activate Darlington Driver)

    PORTC &= 0x0;       //Clean port C
    PORTE &= 0b001;     //Write 0b001 in port E (activate A5 in Darlington diode)
    int count=0;

    PIR1bits.TMR1IF = 0; //Clean Peripherical Interrupt Register 1 (TMR1 flag)
    while(1){
   
            PORTC = 0x80;   //Turn on Led 1 turn off led 2
            Timer_Delay();
            Timer_Delay();
            PORTC = 0x40;  
            Timer_Delay();
            PORTC = 0x20;   //Turn off Led 1 turn on led 2
            Timer_Delay();
            Timer_Delay();
    }
    return;
}

void Timer_Delay(void){ //5 seconds
    
    //PIE1 REGISTER (Peripherical Interrupt Enable Register)
    PIE1bits.TMR1IE |= 0x1;   //Enable Timer1 Interrupt  
 
    TMR1L =0x51; 
    TMR1H =0xB4; 
    
    T1CON &= 0x18; //Configure Timer1 as Internal Clock, 1:2 Prescaler
    T1CONbits.TMR1ON =1; //Timer1 enable bit
    
    //PIR1 REGISTER (Peripherical Interrupt Flag Register)
    while(PIR1bits.TMR1IF == 0);  //Wait until timer interrupt
    PIR1bits.TMR1IF = 0;          //Clean Peripherical Interrupt Register 1 (TMR1 flag)   
}
