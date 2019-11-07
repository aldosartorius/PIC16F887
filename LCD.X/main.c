/*
 * File:   main.c
 * Author: Soul_PC
 *
 * Created on 17 de octubre de 2019, 07:09 AM
 */

#include <xc.h>
#include "LCD_driver.c"

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


int main()
{
    int ia=1;
    unsigned int a;
    TRISD = 0x00;
    Lcd_Start();
    
    while(1){
        
        ia++;
        if(ia ==15){
            ia=1;
        }
        Lcd_Clear(); 
        Lcd_Set_Cursor(1,1);
        Lcd_Print_String("Aldo Sartorius");
        
        if(ia%2 == 0){
           
            Lcd_Set_Cursor(2,ia);
             Lcd_Print_String("PAR");
             __delay_ms(100);
        }
        else{
            
            Lcd_Set_Cursor(2,ia);
             Lcd_Print_String("IMPAR");
             __delay_ms(100);
        }
    }
    return 0;
}