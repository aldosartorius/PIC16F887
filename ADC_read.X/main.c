/*
 * File:   main.c
 * Author: Soul_PC
 *
 * Created on 26 de octubre de 2019, 09:55 AM
 * MISRA 12 verified on November 11, 2019
*/
/*                          ***********                                           */
/*  (Analogic Input) RA0--> *         *                                           */
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

#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)

#include <xc.h>
#include <stdio.h> 
#include "LCD_driver.h"

//Function prototypes
int main(void);
void ADC_Init(void);
void ADC_Read(void);

char char_data[16];             //store float data as char for shown in LCD
unsigned short int_data =0;        //store 10 bits data as hex data
float scaled_float_data = 0;        //store scaled data as float

int main(void) {
    
    //Tri State Control Register (TRIS)
    TRISD = 0x00;  //Port D as digital Output (LCD)
    Lcd_Start();
    Lcd_Clear(); 
    ADC_Init();

    while(1){
        ADC_Read();
     }
}

void ADC_Init(void){
    
    //Tri State Control Register (TRIS)
    TRISA = 0x1;     //Port A pin 0 as input
    
    //Analog Select Register (ANSEL)
    ANSEL = 0x1;     //Port A pin 0 as analog input
    
    // A/D Control register (ADCON0)   
    ADCON0 = 0x1;    //ADC on, Channel 0
    ADCON1 = 0x80;   //Right justified 10 bits data
}

void ADC_Read(void){
    
    for(int i=0 ; i <=2; i++){ //Delay 4 ms, acquisition time to charge hold capacitor
        Timer_Delay();
     }
    // A/D Control register (ADCON0)   
    ADCON0 |= (unsigned char)0x2; //Initializes A/D conversion
    
    while((ADCON0 & (unsigned char)0x2) == 0x2){}; //Wait for A/D conversion
    
    //Copy 10 bits of data adquired
    int_data = (unsigned short)((unsigned short)ADRESH<<8) + (unsigned short)ADRESL;      //MISRA 12 Compliant
    scaled_float_data = (float)((float)((float)int_data*(float)5.000000)/(float)(1023));  //MISRA 12 Compliant
    (void)sprintf(char_data, "%f volts", scaled_float_data);                              //MISRA 12 Compliant

    Lcd_Clear(); 
    Lcd_Set_Cursor((char)1,(char)1);
    Lcd_Print_String((char *)"Voltaje medido");
    Lcd_Set_Cursor((char)2,(char)1);
    Lcd_Print_String(char_data);
     
     for(int i=0 ; i <=100; i++){ //Delay 200 ms antiblink LCD
        Timer_Delay();
     }
}

