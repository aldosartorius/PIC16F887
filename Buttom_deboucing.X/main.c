/*
 * File:   main.c
 * Author: Soul_PC
 *
 * Created on 11 de octubre de 2019, 09:28 AM
* MISRA 12 verified on November 09, 2019
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

 
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
 
#include <xc.h>

//Function prototypes
int main(void);


int main(void) {
    
    TRISCbits.TRISC7 = 0;    //Port C pin 7 configured as Output (Led)
    TRISDbits.TRISD0 = 1;    //Port D pin 0 configured as Input (switch)
    TRISEbits.TRISE0 = 0;    //Port E pin 0 configured as Output (Darlington diode)
    
    PORTCbits.RC7 = 0;       //Clear Port C pin 7
    PORTEbits.RE0 = 0;       //Clear Port E pin 0
            
    while(1){
    
        if(PORTDbits.RD0 == 0){ //Butoom presed
            PORTEbits.RE0 = 1;  //Activate Darlington diode
            PORTCbits.RC7 = 1;  //Turn ON the led
        }
        else if(PORTDbits.RD0 == 1){   //Buttom unpressed
            PORTEbits.RE0 = 0;  //Desactivate Darlington diode
            PORTCbits.RC7 = 0;  //Turn OFF the led
        }
        else{};
    }
}
