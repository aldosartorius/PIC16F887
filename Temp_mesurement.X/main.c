/*
 * File:   main.c
 * Author: Soul_PC
 *
 * Created on 30 de octubre de 2019, 08:37 PM
* MISRA 12 verified on November 11, 2019
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


#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)

#include <xc.h>
#include <stdio.h> 
#include "LCD_driver.h"

//Function prototypes
int main(void);
void ADC_Init(void);
void ADC_Read(void);

unsigned short int_data;
char char_data[16];
float scaled_float_data;
float scaled_temperature;

int main(void){
    
    //Tri State Control Register (TRIS)
    TRISD = 0x00;         //Port D as digital Output (LCD)
    Lcd_Start();
    Lcd_Clear(); 
    ADC_Init();

    while(1){
        ADC_Read();
     }
}

void ADC_Init(void){
    
    //Tri State Control Register (TRIS)
    TRISA = 0x2;     //Port A pin 1 as input
    
    //Analog Select Register (ANSEL)
    ANSEL = 0x2;     //Port A pin 1 as analog input
   
    // A/D Control register (ADCON0)
    ADCON0 = 0x5;    //ADC on, Channel 1
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
    scaled_float_data = (float)((float)((float)int_data*5.0f)/(float)(1023));  //MISRA 12 Compliant, Temperature in volts
    scaled_temperature = scaled_float_data*1000.0f;             //Temperature in miliVolts
    scaled_temperature = scaled_temperature/10.0f;              //Temperature in grades C
    (void)sprintf(char_data, "%f C", scaled_temperature); 

    Lcd_Clear(); 
    Lcd_Set_Cursor((char)1,(char)1);
    Lcd_Print_String((char *)"Temp. actual");
    Lcd_Set_Cursor((char)2,(char)1);
    Lcd_Print_String(char_data);
    for(int i=0 ; i <=100; i++){ //Delay 200 ms antiblink LCD
        Timer_Delay();
     }
}

