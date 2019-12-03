/*
 * File:   main.c
 * Author: Soul_PC
 *
 * Created on 17 de octubre de 2019, 07:09 AM
 * MISRA 12 verified on November 09, 2019
*/
/*                          ***********                                           */
/*                          *         *                                           */
/*  (Analogic Input) RA1--> *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         * -->RD2 (LCD  RS)                          */
/*                          *         * -->RD3 (LCD  R/W)                         */
/*                          *         * -->RD4 (LCD  data)                        */
/*                          *         * -->RD5 (LCD  data)                        */
/*                          *         * -->RD6 (LCD  data)                        */
/*                          *         * -->RD7 (LCD  data)                        */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          ***********                                           */ 


#pragma config WDTE = OFF               // Watchdog Timer Enable bit (WDT disabled)
 
#include <xc.h>
#include <stdio.h> 
#include "LCD_driver.h"

//Function prototypes
int main(void);


int main(void)
{
    
     //Oscillator Control Register (OSCCON)
    OSCCON = 0x71;                      //Define internal oscilator, Fosc = 8 MHz (For timer delay)
   
    //Tri State Control Register (TRIS)
    TRISD = (unsigned char)0x00;        //All port D defined as output
    Lcd_Start();
    
    while(1){
       
        Lcd_Clear(); 
        Lcd_Set_Cursor((char)1,(char)1);
        Lcd_Print_String((char *)"Aldo Sartorius");
        Lcd_Set_Cursor((char)2,(char)1);
        Lcd_Print_String((char *)"Prueba LCD");
        for (int count=0; count<=20; count++ ){
            Timer_Delay();
        }
 
    }
}