//cONECTAR UN BOTON EN PORT B


/*
 * File:   main.c
 * Author: Soul_PC
 *
 * Created on 14 de octubre de 2019, 12:41 PM
 */

// CONFIG1
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include <xc.h>

void Timer_Delay(void);

void main(void) {
    
    TRISCbits.TRISC7 = 0;    //Port C pin 7 configured as Output (Led)
    TRISBbits.TRISB4 = 1;    //Port B pin 7 configured as Input (switch)
    TRISEbits.TRISE0 = 0;    //Port E pin 0 configured as Output (Darlington diode)
    
    PORTCbits.RC7 = 0;       //Clear Port C pin 7
    PORTEbits.RE0 = 0;       //Clear Port E pin 0
         
   
    WPUBbits.WPUB4 = 1;
   
   
    
    
    //INTCON Interrupt Control Register
    INTCONbits.RBIF =0;   //Clear Interrup On Change Port B flag 
    
     //IOCB  Interrupt On Change port B
    IOCBbits.IOCB5 = 1;//0b11111111;//FF;      //Enable Interrup On Change in Pin 7 of port B (Buttom)
    
  INTCONbits.RBIE =1;
    
      //Enable global Interrupt
    INTCONbits.GIE = 1;
    
    // INTCONbits.INTF = 0;  //Internal interrupt flag bit
    //INTCONbits.INTE = 1;  //Internal interrupt enable bit
    
    while(1){
       
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

void __interrupt() MyISR(){

    //Identyfi Interrupt source
    if(INTCONbits.RBIF == 1){
        PORTEbits.RE0 = 1;
        PORTCbits.RC7 = 1;
        Timer_Delay();
        Timer_Delay();
        Timer_Delay();
        Timer_Delay();
       // PORTEbits.RE0 = 0;
        //PORTCbits.RC7 = 0;
        
        INTCONbits.RBIF = 0;
       
    }

}
