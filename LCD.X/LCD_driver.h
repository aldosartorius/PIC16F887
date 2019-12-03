/* 
 * File:   LCD_driver.h
 * Author: Soul_PC
 *
 * Created on 9 de noviembre de 2019, 12:11 PM
 */

#ifndef LCD_DRIVER_H
#define	LCD_DRIVER_H

#include<pic16f887.h>

void Lcd_SetBit(char data_bit);
void Lcd_Cmd(char a);
void Lcd_Clear(void);
void Lcd_Set_Cursor(char row, char column);
void Lcd_Start(void);
void Lcd_Print_Char(char data);
void Lcd_Print_String(char *a);
void Timer_Delay(void);


#endif	/* LCD_DRIVER_H */

