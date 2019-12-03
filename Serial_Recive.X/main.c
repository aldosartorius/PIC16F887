/*
 * File:   main.c
 * Author: Soul_PC
 *
 * Created on 25 de noviembre de 2019, 09:20 AM
* MISRA 12 verified on November 22, 2019
*/
/*                          ***********                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         * <-- RC7 (Rx)                              */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         * -->RD3 (LCD  R/W)                         */
/*                          *         * -->RD4 (LCD  data)                        */
/*                          *         * -->RD5 (LCD  data)                        */
/*                          *         * -->RD6 (LCD  data)                        */
/*                          *         * -->RD7 (LCD  data)                        */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          ***********                                           */

#pragma config WDTE = OFF  //WatchDog Off 

#include <xc.h>
#include <stdio.h> 
#include "LCD_driver.h"
 
 
//Function prototipes 
int main(void);
void Init_Clock(void);
void Init_USART(void);
void receive_char(void);


char rc_data_char;
unsigned short i;    //array index variable

 
 int main(void) {
    
    //Tri State Control Register (TRIS)
     
    TRISD = (unsigned char)0x00;        //All port D defined as output
   TRISCbits.TRISC7 =1;                 //Port C bit 7 (RC7) as input
    
    Init_Clock();
    Init_USART();
    
    INTCONbits.PEIE = 1;                // Enable peripheral interrupts
    INTCONbits.GIE = 1;                 // Enable global interrupts
    
   
    RCREG = 0x0;
   
    Lcd_Start();
    Lcd_Clear(); 
     
    while(1){
        
        // Lcd_Clear(); 
        Lcd_Set_Cursor((char)1,(char)1);
        Lcd_Print_String((char *)"Dato recibido");
        receive_char();
        Lcd_Set_Cursor((char)2,(char)i);
        Lcd_Print_Char(rc_data_char);
        for (int count=0; count<=20; count++ ){
            Timer_Delay();
        }
       
   
       
    }
}

void Init_Clock(void){
    
    //Oscillator Control Register (OSCCON)
    OSCCON = 0x71;          //Define internal oscilator, Fosc = 8 MHz
}

void Init_USART(void){

    SPBRG = 0xC;
    
    //Transmit Status & Control Register (TXSTA)
    TXSTAbits.BRGH = 0;       //low speed baud rate
    TXSTAbits.SYNC = 0;       //Asynchronous comunication
    
    //Baud Rate Control Register (BAUDCTL)
    BAUDCTLbits.BRG16 = 0;    //8-bit Baud Rate Generator is used

    //Recive Status & Control Register (RCSTA)
    RCSTAbits.SPEN = 1;      //Serial port enabled (configures RX/DT and TX/CK pins as serial port pins)
    
    //TXSTAbits.TXEN = 1;       //Transmit enabled  
    RCSTAbits.CREN = 1;       //Recive enabled
    
    //PIE1 Register (Peripherical Interrupt Enable Register)
    PIE1bits.RCIE =1;        //EUSART Recive Interrupt Enable bit

}

void receive_char(void){
   
    if(PIR1bits.RCIF == 1){
        rc_data_char= (char)RCREG;
         if(i == 16){
             i = 0;
          }
        i++;
    } 
}
