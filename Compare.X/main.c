/*
 * File:   main.c
 * Author: Soul_PC
 *
 * Created on 12 de noviembre de 2019, 07:55 AM
 * MISRA 12 verified on November 15, 2019
*/
/*                          ***********                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *-->RC2 (CCP1) (PWM)                        */
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
#pragma config WDTE = OFF  //WatchDog Off 

#include <xc.h>

//Function prototypes
int main(void);
void Init_Clock(void);
void Init_Ports(void);
void Init_Compare_Mode(void);
void Init_Timer1(void);


int main(void) {
    
    Init_Clock();
    Init_Ports();
    Init_Compare_Mode();
    Init_Timer1();

    //Interrrup Control Register (INTCON)
    INTCONbits.PEIE =1;    //Peripherical Interrupt Enable bit

   //Interrrup Control Register (INTCON)
    INTCONbits.GIE = 1;   //Global Interrupt Enable bit

    while(1){
    }
}

void Init_Clock(void){
    
    //Oscillator Control Register (OSCCON)
    OSCCON = 0x01;          //Define internal oscilator, Fosc = 31 Khz

}
void Init_Ports(void){

    //Analog Select Register (ANSEL)
    ANSEL = 0x0;            //Disable  port A as analogic port (Energy saving, Port A enable darlington diodes for 7 segments)
    ANSELH = 0x0;           //Disable  port B as analogic port (Energy saving, Port B Reads butoms)
    
    //Tri State Control Register (TRIS)
    TRISC = 0x00;           //Port C as digital Output (Diodes)
    TRISE = 0x00;           //Port E as digital Output (Darlington diode)
    
    PORTC = 0x00;           //Clean all port C
    PORTEbits.RE0 = 1;      //Activate Darlington diode for LED 2 conected in port RC2/CCP1
}

void Init_Compare_Mode(void){
    
    //Enhaced CCP1 Control Register (CCP1CON)
    CCP1CON = 0x2;          //Compare mode, toggle output on match (CCP1IF bit is set)

    //PIE1 Register (Peripherical Interrupt Enable Register)
    PIE1bits.CCP1IE = 1;    //Enable CCP1 Interrupt  

    //PIR1 Register (Peripherical Interrupt Request)
    PIR1bits.CCP1IF = 0;    //Clean Peripherical Interrupt Register 1 (CCP1 flag)

    //Set CCP time at 5 seconds
    CCPR1L = 0xAF;         //Holding Register for the Least Significant Byte of the 16-bit CCPR1 Register 
    CCPR1H = 0x4B;         //Holding Register for the Most Significant Byte of the 16-bit CCPR1 Register 

}

void Init_Timer1(void){    //15 seconds 
    
   //PIE1 REGISTER (Peripherical Interrupt Enable Register)
   PIE1bits.TMR1IE = 1;    //Enable Timer1 Interrupt  
 
    //Set Timer1 time at 0 seconds
    TMR1L = 0x00;         //Holding Register for the Least Significant Byte of the 16-bit TMR1 Register 
    TMR1H = 0x00;         //Holding Register for the Most Significant Byte of the 16-bit TMR1 Register 
    
    //Timer1 Control Register (T1CON)
    T1CON = 0x10;         //Configure Timer1 as Internal Clock, 1:2 Prescaler
  
    //PIR1 Register (Peripherical Interrupt Request)
    PIR1bits.TMR1IF =0;   //Clean Peripherical Interrupt Register 1 (TMR1 flag)
    
    //Timer1 Control Register (T1CON)
    T1CONbits.TMR1ON = 1; //Timer1 enable bit
    
}

void __interrupt() MyISR(){

    if(PIR1bits.CCP1IF == 1){
    
        //Set Timer1 time at 0 seconds
        TMR1L = 0x00;         //Holding Register for the Least Significant Byte of the 16-bit TMR1 Register 
        TMR1H = 0x00;         //Holding Register for the Most Significant Byte of the 16-bit TMR1 Register 

        //PIR1 Register (Peripherical Interrupt Request)
        PIR1bits.CCP1IF = 0;    //Clean Peripherical Interrupt Register 1 (CCP1 flag)
    }
}






