/*
 * File:   main.c
 * Author: Soul_PC
 *
 * Created on 25 de noviembre de 2019, 09:20 AM
* MISRA 12 verified on November 29, 2019
*/
/*                          ***********                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         * --> RC6 (Tx)                              */
/*                          *         * <-- RC7 (Rx)                              */
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

#pragma config WDTE = OFF  //WatchDog Off 

#include <xc.h>
#include <stdio.h> 
#include "LCD_driver.h"

//Function prototipes 
int main(void);
void Init_Clock(void);
void Init_USART(void);
void Send_Char_USART(char character);
void Send_String_USART(const char * str);
void Init_ADC(void);
void Read_ADC(void);

//Global varibles for data adquisition
unsigned short int_data;
char char_data[9];
float scaled_float_data;
float scaled_temperature;

//Global variable for serial data recived
 char rc_data[10];

 
 int main(void) {
    
        //Tri State Control Register (TRIS)
        TRISD = 0x00;        //All port D defined as output
        TRISCbits.TRISC7 =1; //Pin 7 of port D as input (Rx))

        Init_Clock();
        Init_ADC();
        Init_USART();

        INTCONbits.PEIE = 1; // Enable peripheral interrupts
        INTCONbits.GIE = 1; // Enable global interrupts

        TXREG = 0x0;
        RCREG = 0x0;

        Lcd_Start();
        Lcd_Clear(); 
        Lcd_Set_Cursor((char)1,(char)1);
        Lcd_Print_String((char *)"Temperatura");
     
    while(1){
   
        Read_ADC();
        Send_String_USART(char_data);
        Lcd_Set_Cursor((char)2,(char)1);
        Lcd_Print_String(char_data);
        for(int i=0 ; i <=50; i++){ //Delay 100 ms antiblink LCD
            Timer_Delay();
         } 
    }
}

void Init_Clock(void){
    
    //Oscillator Control Register (OSCCON)
    OSCCON = 0x71;          //Define internal oscilator, Fosc = 8 MHz
}

void Init_USART(void){

    SPBRG = 0xC;              //Define 9600 bps connection
    
    //Transmit Status & Control Register (TXSTA)
    TXSTAbits.BRGH = 0;       //low speed baud rate
    TXSTAbits.SYNC = 0;       //Asynchronous comunication
    
    //Baud Rate Control Register (BAUDCTL)
    BAUDCTLbits.BRG16 = 0;    //8-bit Baud Rate Generator is used

    //Recive Status & Control Register (RCSTA)
    RCSTAbits.SPEN = 1;      //Serial port enabled (configures RX/DT and TX/CK pins as serial port pins)
    
    TXSTAbits.TXEN = 1;       //Transmit enabled  
    RCSTAbits.CREN = 1;       //Recive enabled
    
    //PIE1 Register (Peripherical Interrupt Enable Register)
    PIE1bits.RCIE =1;        //EUSART Recive Interrupt Enable bit

}

void Send_Char_USART(char character){

    while(PIR1bits.TXIF == 0){};
    PIR1bits.TXIF = 0;
    TXREG = (unsigned char)character; 
}

void Send_String_USART(const char * str){
    short i=0;
    while(str[i] != 0){                 //0 means final string character
        Send_Char_USART(str[i]);        //Transmmit character i
        i++;
    }
}

void Init_ADC(void){
    
    //Tri State Control Register (TRIS)
    TRISA = 0x2;     //Port A pin 1 as input
    
    //Analog Select Register (ANSEL)
    ANSEL = 0x2;     //Port A pin 1 as analog input
   
    // A/D Control register (ADCON0)
    ADCON0 = 0x5;    //ADC on, Channel 1
    ADCON1 = 0x80;   //Right justified 10 bits data
}

void Read_ADC(void){
    
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
   (void)sprintf(char_data, "%f\r", scaled_temperature);     
}


