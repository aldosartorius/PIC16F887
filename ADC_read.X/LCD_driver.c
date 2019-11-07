
#define _XTAL_FREQ 80000000

#define RS RD2      //Register Select
#define EN RD3      //LCD Enable
#define D4 RD4      //Data line
#define D5 RD5      //Data line
#define D6 RD6      //Data line
#define D7 RD7      //Data line


void Lcd_SetBit(char data_bit) //Based on the hex value set the bits of the data lines
{
    if(data_bit & 1)     //0001
        D4 = 1;
    else
        D4 = 0;

    if(data_bit & 2)    //0010
        D5 = 1;
    else
        D5 = 0;

    if(data_bit & 4)    //0100
        D6 = 1;
    else
        D6 = 0;

    if(data_bit & 8)    //1000
        D7 = 1;
    else
        D7 = 0;
}

void Lcd_Cmd(char a)
{
    RS = 0;           
    Lcd_SetBit(a); //Incoming Hex value
    EN  = 1;         
    __delay_ms(2);
    EN  = 0;         
}

void Lcd_Clear()
{
    Lcd_Cmd(0x00); //Clear the LCD
    Lcd_Cmd(0x01);    //Clear display & return home 
  
}

void Lcd_Set_Cursor(char row, char column)    
{
    char temp,z,y;
    if(row == 1)
    {
        temp = 0x80 + column - 1; //0x80 cursor at beginninn of the firs line is used to move the curser
        z = temp>>4; //Upper 4-bits contain row position
        y = temp & 0x0F; //Lower 4-bits contanin column position
        Lcd_Cmd(z); //Set Row
        Lcd_Cmd(y); //Set Column
    }
    else if(row == 2)
    {
        temp = 0xC0 + column - 1; //0xC0 cursor at beginninn of the second line
        z = temp>>4; //Upper 4-bits contain row position
        y = temp & 0x0F; //Lower 4-bits contanin column position
        Lcd_Cmd(z); //Set Row
        Lcd_Cmd(y); //Set Column
    }
}

void Lcd_Start()
{

  Lcd_SetBit(0x00);             
  //for(int i=1065244; i<=0; i--)  NOP();  
  //Lcd_Cmd(0x03); //0b0011
  //  __delay_ms(5);
  Lcd_Cmd(0x03);    //Clear display & return home 
    //__delay_ms(11);
  Lcd_Cmd(0x03); 
  Lcd_Cmd(0x02); //02H is used for Return home -> Clears the RAM and initializes the LCD
  Lcd_Cmd(0x02); //02H is used for Return home -> Clears the RAM and initializes the LCD
  Lcd_Cmd(0x08); //Select Row 1
  Lcd_Cmd(0x00); //Clear Row 1 Display
  Lcd_Cmd(0x0C); //Select Row 2
  Lcd_Cmd(0x00); //Clear Row 2 Display
  Lcd_Cmd(0x06);
}

void Lcd_Print_Char(char data)  //Send 8-bits through 4-bit mode
{
   char Lower_Nibble,Upper_Nibble;
   Lower_Nibble = data&0x0F;
   Upper_Nibble = data&0xF0;
   RS = 1;             // => RS = 1
   Lcd_SetBit(Upper_Nibble>>4);             //Send upper half by shifting by 4
   EN = 1;
  // for(int i=2130483; i<=0; i--)  NOP(); 
   EN = 0;
   Lcd_SetBit(Lower_Nibble); //Send Lower half
   EN = 1;
 // for(int i=2130483; i<=0; i--)  NOP();
   EN = 0;
}

void Lcd_Print_String(char *a)
{
    int i;
    for(i=0;a[i]!='\0';i++)
       Lcd_Print_Char(a[i]);  //Split the string using pointers and call the Char function 
}

 

