/*
 * File:   main.c
 * Author: Soul_PC
 *
 * Created on 14 de octubre de 2019, 11:59 AM
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
    
    short flag = 0;
    TRISCbits.TRISC7 = 0;    //Port C pin 7 configured as Output (Led)
    TRISDbits.TRISD0 = 1;    //Port D pin 0 configured as Input (switch)
    TRISEbits.TRISE0 = 0;    //Port E pin 0 configured as Output (Darlington diode)
    
    PORTCbits.RC7 = 0;       //Clear Port C pin 7
    PORTEbits.RE0 = 0;       //Clear Port E pin 0
            
    while(1){
    
        if(PORTDbits.RD0 == 0 ){ //Butoom presed
            if(flag == 0){
                PORTEbits.RE0 = 1;  //Activate Darlington diode
                PORTCbits.RC7 = 1;  //Turn ON the led
                flag = 1;           //activate flag
                
            }
            else{
                PORTEbits.RE0 = 0;  //Desactivate Darlington diode
                PORTCbits.RC7 = 0;  //Turn OFF the led
                flag = 0;           //Desactivate flag
            
            }
            
        }
        Timer_Delay();   //.07 s
        Timer_Delay();
   
       
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
