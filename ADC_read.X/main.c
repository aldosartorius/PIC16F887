/*
 * File:   main.c
 * Author: Soul_PC
 *
 * Created on 26 de octubre de 2019, 09:55 AM
 */

#pragma config FOSC = EXTRC_CLKOUT// Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
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


#include <xc.h>
#include <stdio.h> 
#include "LCD_driver.c"

int int_data;
char char_data[16];
float scaled_int_data;

void ADC_Init(void);
void ADC_Read(void);


void main(void) {
    
    TRISD = 0x00;  //LCD
    Lcd_Start();
    Lcd_Clear(); 
    ADC_Init();

    while(1){
     
        ADC_Read();
     }
     
     
    return;
}

void ADC_Init(){
    
    TRISA = 0x1;     //Port A pin 0 as input
    ANSEL = 0x1;     //Port A pin 0 as analog input
    ADCON0 = 0x1;    //ADC on, Channel 0
    ADCON1 = 0x80;   //Right justified 10 bits data
}

void ADC_Read(){
    
    __delay_ms(4);               //Acquisition time to charge hold capacitor
    GO_nDONE = 1;                //Initializes A/D conversion
    while(GO_nDONE);             //Wait for A/D conversion
    
    int_data =  (ADRESH<<8) + ADRESL;  
    scaled_int_data =((float)(int_data*5)/(float)(1023));
    sprintf(char_data, "%f volts", scaled_int_data); 

    Lcd_Clear(); 
    Lcd_Set_Cursor(1,1);
    Lcd_Print_String("Voltaje medido");
    Lcd_Set_Cursor(2,1);
    Lcd_Print_String(char_data);
    __delay_ms(200);
}

