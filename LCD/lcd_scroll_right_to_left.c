/*
  LCD Right-to-Left Scrolling Program
 
  -Displays "EMBEDDED" on Line 1 and
  -scrolls "SYSTEMS" from right to left
   on Line 2 of a 16x2 LCD.
 */
#include <LPC213x.h>
#include "lcd.h"

int main(void)
{
	int32_t i;
	LCD_init();
	
	//print centered on line 1
	LCD_cmd(LCD_LINE1+4);
	LCD_str("EMBEDDED");
	
	while(1)
	{
		//Scroll from right to left
		for(i=9;i>=0;i--) //start_position=(16-text_length)
		{
		LCD_cmd(LCD_LINE2);
		LCD_str("                "); // 16 spaces
		
		LCD_cmd(LCD_LINE2+i);  //Print text at new position
		LCD_str("SYSTEMS");
		delay_ms(200);
	  }
  }  
}
