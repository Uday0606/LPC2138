/*
   Embedded C Program to develop a driver for 16x2 LCD to:
   a) Display a character
   b) Display a string
   c) Display an integer
   d) Display a float up to 2 decimal places
	 e) display any custom character. 
	 
    Data lines  P0.8 – P0.15.
		RS -P0.4, RW -P0.5, EN -P0.6
 */
#include <LPC213x.h>
#include "lcd.h"

uint8_t smiley[8]={0X00,0X0A,0X00,0X00,0X11,0X0E,0X00,0X00};
 
int main(void)
{
	LCD_init(); 
	
	LCD_data('A');  //display single char
	delay_ms(1000);
	LCD_cmd(LCD_CLR);
	
	LCD_str("Embedded Systems");  //display string
	delay_ms(1000);
	LCD_cmd(LCD_CLR);
	
	LCD_str("Integer: "); //display integer
	LCD_int(-440);
	delay_ms(1000);
	LCD_cmd(LCD_CLR);
	
	LCD_str("Float: ");
	LCD_float(-12.3456f,2);
	delay_ms(1000);
	LCD_cmd(LCD_CLR);
	
	LCD_custom_char(0,smiley);
	LCD_data(0);
	
	while(1);
}
