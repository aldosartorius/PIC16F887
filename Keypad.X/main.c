
/*
 * File:   main.c
 * Author: Soul_PC
 *
 * Created on 22 de octubre de 2019, 09:44 AM
 * MISRA 12 verified on November 09, 2019
*/
/*                          ***********                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*           (KeyPad) RB0<--*         *                                           */
/*           (KeyPad) RB1<--*         *                                           */
/*           (KeyPad) RB2<--*         *                                           */
/*           (KeyPad) RB3<--*         *                                           */
/*           (KeyPad) RB4-->*         *                                           */
/*           (KeyPad) RB5-->*         * -->RD2 (LCD  RS)                          */
/*           (KeyPad) RB6-->*         * -->RD3 (LCD  R/W)                         */
/*           (KeyPad) RB7-->*         * -->RD4 (LCD  data)                        */
/*                          *         * -->RD5 (LCD  data)                        */
/*                          *         * -->RD6 (LCD  data)                        */
/*                          *         * -->RD7 (LCD  data)                        */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          ***********                                           */ 


#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)


#include <xc.h>
#include "LCD_driver.h"

//Function prototypes
int main(void);
void seek_press_key(void);
void __interrupt() MyISR(void);

int main(void) {
    
    //Tri State Control Register (TRIS)
    TRISD = 0x00;                     ////All port D defined as output             

    Lcd_Start();
    Lcd_Clear(); 
    
    //Analog Select Register (ANSEL)
    ANSEL &= (unsigned char)0x0;       //Disable  port A as analogic port (Energy saving, Port A enable darlington diodes for LCD)
    ANSELH &=(unsigned char)0x0;       //Disable  port B as analogic port (Energy saving, Port B Reads butoms)
   
    //Keypad is connected at port B
    //Tri State Control Register (TRIS)
    TRISB = 0xF0;                      //0b1111000  firts nible as output, second nible as input
    PORTB &= (unsigned char)0x0F;

    //IOCB  Interrupt On Change port B
    IOCB = 0xC0;                      //0b1100000   

    //INTCON Interrupt Control Register
    INTCONbits.RBIF =0;                //Clear Interrup On Change Port B flag 

    INTCONbits.RBIE =1;                //Interupt On Change Port B enable

    //Enable global Interrupt
    INTCONbits.GIE = 1;

    while(1){};

}

void __interrupt() MyISR(void){

    if(INTCONbits.RBIF == 1 ){       
        seek_press_key();

    }
    INTCONbits.RBIF = 0;                //Clear Interrup On Change Port B flag 
  
}

void seek_press_key(void){


    if(PORTBbits.RB6 == 1){

        //CI High
        TRISB = 0xFE;   //0b1111 1110
        PORTB = 0x01;  //0b0000 0001
        if(PORTBbits.RB6 == 1 ){
                Lcd_Clear();
                Lcd_Set_Cursor((char)1,(char)1);
                Lcd_Print_String((char *)"9");
        }
        else{
            //C2 High
            TRISB = 0xFD;   //0b1111 1101
            PORTB = 0x02;  //0b0000 0010
            if(PORTBbits.RB6 == 1 ){
                    Lcd_Clear();
                    Lcd_Set_Cursor((char)1,(char)1);
                    Lcd_Print_String((char *)"10");
            }
            else{
                //C3 High
                TRISB = 0xFB;   //0b1111 1011
                PORTB = 0x04;  //0b0000 0100
                if(PORTBbits.RB6 == 1 ){
                        Lcd_Clear();
                        Lcd_Set_Cursor((char)1,(char)1);
                        Lcd_Print_String((char *)"11");
                 }
                else{
                        Lcd_Clear();
                        Lcd_Set_Cursor((char)1,(char)1);
                        Lcd_Print_String((char *)"12");

                }
            }
        }
    }
    else if (PORTBbits.RB7 == 1){

        //CI High
        TRISB = 0xFE;   //0b1111 1110
        PORTB = 0x01;  //0b0000 0001
        if(PORTBbits.RB7 == 1 ){
                Lcd_Clear();
                Lcd_Set_Cursor((char)1,(char)1);
                Lcd_Print_String((char *)"13");
        }
        else{
            //C2 High
            TRISB = 0xFD;   //0b1111 1101
            PORTB = 0x02;  //0b0000 0010
            if(PORTBbits.RB7 == 1 ){
                    Lcd_Clear();
                    Lcd_Set_Cursor((char)1,(char)1);
                    Lcd_Print_String((char *)"14");
            }
            else{
                //C3 High
                TRISB = 0xFB;   //0b1111 1011
                PORTB = 0x04;  //0b0000 0100
                if(PORTBbits.RB7 == 1 ){
                        Lcd_Clear();
                        Lcd_Set_Cursor((char)1,(char)1);
                        Lcd_Print_String((char *)"15");
                 }
                else{
                        Lcd_Clear();
                        Lcd_Set_Cursor((char)1,(char)1);
                        Lcd_Print_String((char *)"16");

                }
            }
        }
    }
    else{};
    
 TRISB = 0xF0;    
 PORTB = 0x0F;

}
