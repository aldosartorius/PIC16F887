/*
 * File:   main.c
 * Author: Soul_PC
 *
 * Created on September 30, 2019, 12:34 PM
 */


#include <xc.h>


void delay(void);  

void main(void) {
    
   OSCCON = 111; //Define 8 mHZ

    ANSEL &= 0x0;        //Disable  port A as analogic port (Energy saving, Port A enable darlington diodes for LCD)
    ANSELH &=0x0;        //Disable  port B as analogic port (Energy saving, Port B Reads butoms)
    
  
    //Tri state control register
    TRISC &= 0x0;        //all C port as Output
    TRISE &= 0x0;        //all E port as Output (Port E activate Darlington Driver)

    PORTC &= 0x0;       //Clean port C
    PORTE &= 0b001;     //Write 0b001 in port E (activate A5 in Darlington diode)
    
    while(1){
        delay();
        PORTC = 0x1;   //Turn on Led 1 turn off led 2
        delay();
        PORTC = 0x4;   //Turn off Led 1 turn on led 2
        delay();
        
    }
    return;
}

void delay(void){
    int i,j;
    for  (i = 0; i < 2;  i++){
            for (j = 0; j < 10000;  j++);
        
    }

}
