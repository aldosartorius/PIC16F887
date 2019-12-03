/*
 * File:   main.c
 * Author: Soul_PC
 *
 * Created on 14 de octubre de 2019, 11:59 AM
 * MISRA 12 verified on November 10, 2019
*/
/*                          ***********                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *-->RC7 (Led 7)                             */
/*                          *         *<--RD0 (Buttom)                            */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *--> RE0 UL2803A (Darlington diode)         */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          ***********                                           */ 



// CONFIG1

#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)

#include <xc.h>

//Function prototypes
int main(void);
void Timer_Delay(void);

int main(void) {
    
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
}


void Timer_Delay(void){  //Two seconds delay
    
    //PIE1 REGISTER (Peripherical Interrupt Enable Register)
    PIE1 &= (unsigned char)0x1;    //Enable TMR1 Interrupt
    TMR1L = 0x90;                  //Preload charge data
    TMR1H = 0xFD;                  //Preload charge data
    T1CON |= (unsigned char)0x1;   //Enable TMR1
    while(PIR1bits.TMR1IF == 0){};   //Wait until timer interrupt
    PIR1bits.TMR1IF = 0;           //Clean Peripherical Interrupt Register 1 (TMR1 flag)  
}
