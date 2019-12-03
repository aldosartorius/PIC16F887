/*
 * File:   main.c
 * Author: Soul_PC
 *
 * Created on 15 de noviembre de 2019, 03:45 PM
* MISRA 12 verified on November 15, 2019
*/
/*                          ***********                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *-->RC2 (CCP1) (PWM 10 kHz 70%)             */
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
void Init_PWM(void);
void Init_Timer2(void);


int main(void) {
    
    Init_Clock();
    Init_Ports();
    Init_PWM();
    Init_Timer2();

    //Interrrup Control Register (INTCON)
    INTCONbits.PEIE =1;    //Peripherical Interrupt Enable bit

   //Interrrup Control Register (INTCON)
    INTCONbits.GIE = 1;   //Global Interrupt Enable bit

    while(1){
    
    }
}

void Init_Clock(void){
    
    //Oscillator Control Register (OSCCON)
    OSCCON = 0x61;          //Define internal oscilator, Fosc = 4 MHz
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

void Init_PWM(void){
    
    PR2 = 0x63;
    
    //Enhaced CCP1 Control Register (CCP1CON)
    CCP1CON = 0xD;          //PWM mode, 1101 P1A, P1C active-high; P1B, P1D active-low
 

    //PIE1 Register (Peripherical Interrupt Enable Register)
    PIE1bits.CCP1IE = 1;    //Enable CCP1 Interrupt  

    //PIR1 Register (Peripherical Interrupt Request)
    PIR1bits.CCP1IF = 0;    //Clean Peripherical Interrupt Register 1 (CCP1 flag)

    //Set duty cycle at 70%
    CCPR1L = 0x46;         //Holding Register for the MOST Significant 8 bits of the duty cycle in CCPR1 Register 
}

void Init_Timer2(void){    //15 seconds 
    
   //PIE1 REGISTER (Peripherical Interrupt Enable Register)
   PIE1bits.TMR2IE = 1;    //Enable Timer1 Interrupt  
 
    //Set Timer1 time2 at 0 seconds
    TMR2 = 0x00;         
  
    //Timer2 Control Register (T1CON)
    T2CON = 0x0;          //Configure Timer2 as  1:1 Prescaler and 1:1 Poscaler
  
    //PIR1 Register (Peripherical Interrupt Request)
    PIR1bits.TMR2IF =0;   //Clean Peripherical Interrupt Register 1 (TMR1 flag)
    
    //Timer1 Control Register (T1CON)
    T2CONbits.TMR2ON = 1; //Timer1 enable bit  
}






