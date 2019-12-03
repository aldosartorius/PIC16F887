/*
 * File:   main.c
 * Author: Soul_PC
 *
 * Created on 20 de noviembre de 2019, 12:36 PM
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
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         * --> RC6 (Tx)                              */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          *         *                                           */
/*                          ***********                                           */

#pragma config WDTE = OFF  //WatchDog Off 

#include <xc.h>

//Function prototypes
int main(void);
void Init_Ports(void);
void Init_Clock(void);
void Init_USART(void);
void Send_Char_USART(char character);
void Send_String_USART(const char * str);


int main(void) {
    
    Init_Clock();
    Init_Ports();
    Init_USART();
    TXREG = 0x0;
    while(1){
        
//        Send_Char_USART('A');
//        Send_Char_USART('l');
//        Send_Char_USART('d');
//        Send_Char_USART('o');
//        Send_Char_USART(' ');
        Send_String_USART("Hola Jazmin Bienvenida al TEC \r\n");
    }
}

void Init_Ports(void){
    
    //Analog Select Register (ANSEL)
    ANSEL &= (unsigned char)0x0;       //Disable  port A as analogic port (Energy saving, Port A enable darlington diodes for LCD)
    ANSELH &=(unsigned char)0x0;       //Disable  port B as analogic port (Energy saving, Port B Reads butoms)

    //Tri State Control Register (TRIS)
    TRISD = (unsigned char)0x00;       //All port D defined as output
     
    PORTD = (unsigned char)0x0;        //Clear port D
}

void Init_Clock(void){
    
    //Oscillator Control Register (OSCCON)
    OSCCON = 0x71;          //Define internal oscilator, Fosc = 8 MHz
}

void Init_USART(void){

    //PIE1 Register (Peripherical Interrupt Enable Register)
    PIE1bits.TXIE =1;        //EUSART Transmit Interrupt Enable bit

    SPBRG = 0xC;
    
    //Transmit Status & Control Register (TXSTA)
    TXSTAbits.BRGH = 0;       //low speed baud rate
    TXSTAbits.SYNC = 0;       //Asynchronous comunication
    
    //Baud Rate Control Register (BAUDCTL)
    BAUDCTLbits.BRG16 = 0;    //8-bit Baud Rate Generator is used

    //Recive Status & Control Register (RCSTA)
    RCSTAbits.SPEN = 1;      //Serial port enabled (configures RX/DT and TX/CK pins as serial port pins)
    
    TXSTAbits.TXEN = 1;       //Transmit enabled  
}

void Send_Char_USART(char character){
  
    while(PIR1bits.TXIF == 0){};        //Wait until a previous character is send
    PIR1bits.TXIF = 0;                  //Reset flag 
    TXREG = (unsigned char)character;   //Transmmit one character
}

void Send_String_USART(const char * str){
    short i=0;
    while(str[i] != 0){                 //0 means final string character
        Send_Char_USART(str[i]);        //Transmmit character i
        i++;
    }
}
