
#include <pic16f887.h>

/*
 * File:   main.c
 * Author: Soul_PC
 *
 * Created on 22 de octubre de 2019, 09:44 AM
 */
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


#include <xc.h>
#include "LCD_driver.c"

void __seek_press_key(void);

void main(void) {
    
    //Keypad is connected at port B
    
    TRISD = 0x00;

    Lcd_Start();
    Lcd_Clear(); 
    
   
    ANSELH =0x0;
  
    TRISB = 0xF0;  //0b1111000  firts nible as output, second nible as input
   
    WPUB &= 0x0F;//000001;
    PORTB &= 0x0F;

    //IOCB  Interrupt On Change port B

    IOCB = 0xC0;

    //INTCON Interrupt Control Register
    INTCONbits.RBIF =0;   //Clear Interrup On Change Port B flag 

    INTCONbits.RBIE =1;

    //Enable global Interrupt
    INTCONbits.GIE = 1;

    while(1){
        

       }


    return;
}

void __interrupt() MyISR(){

    if(INTCONbits.RBIF == 1 ){
        __seek_press_key();

    }
    INTCONbits.RBIF = 0;
  
}

void __seek_press_key(){
//if(INTCONbits.RBIF == 1 ){

        if(PORTBbits.RB6 == 1){
            
            //CI High
            TRISB = 0xFE;   //0b1111 1110
            PORTB = 0x01;  //0b0000 0001
            if(PORTBbits.RB6 == 1 ){
                    Lcd_Clear();
                    Lcd_Set_Cursor(1,1);
                    Lcd_Print_String("9");
                    __delay_ms(10);
            }
            else{
                //C2 High
                TRISB = 0xFD;   //0b1111 1101
                PORTB = 0x02;  //0b0000 0010
                if(PORTBbits.RB6 == 1 ){
                        Lcd_Clear();
                        Lcd_Set_Cursor(1,1);
                        Lcd_Print_String("10");
                        __delay_ms(10);
                }
                else{
                    //C3 High
                    TRISB = 0xFB;   //0b1111 1011
                    PORTB = 0x04;  //0b0000 0100
                    if(PORTBbits.RB6 == 1 ){
                            Lcd_Clear();
                            Lcd_Set_Cursor(1,1);
                            Lcd_Print_String("11");
                            __delay_ms(10);
                     }
                    else{
                            Lcd_Clear();
                            Lcd_Set_Cursor(1,1);
                            Lcd_Print_String("12");
                            __delay_ms(10);
                    
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
                    Lcd_Set_Cursor(1,1);
                    Lcd_Print_String("13");
                    __delay_ms(10);
            }
            else{
                //C2 High
                TRISB = 0xFD;   //0b1111 1101
                PORTB = 0x02;  //0b0000 0010
                if(PORTBbits.RB7 == 1 ){
                        Lcd_Clear();
                        Lcd_Set_Cursor(1,1);
                        Lcd_Print_String("14");
                        __delay_ms(10);
                }
                else{
                    //C3 High
                    TRISB = 0xFB;   //0b1111 1011
                    PORTB = 0x04;  //0b0000 0100
                    if(PORTBbits.RB7 == 1 ){
                            Lcd_Clear();
                            Lcd_Set_Cursor(1,1);
                            Lcd_Print_String("15");
                            __delay_ms(10);
                     }
                    else{
                            Lcd_Clear();
                            Lcd_Set_Cursor(1,1);
                            Lcd_Print_String("16");
                            __delay_ms(10);

                    }
                }
            }
        }
        
       
 TRISB = 0xF0;    
 PORTB = 0x0F;

}
