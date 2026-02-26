#include <LPC213x.h>
#include "lcd.h"

int main(void)
{
	uint32_t i;
	LCD_init();
	LCD_cmd(LCD_LINE1);
	LCD_str("HARDIK");
	
	LCD_cmd(LCD_LINE2);
	LCD_str("PANDYA");
	delay_ms(1000);
	for(i=0;i<5;i++) //flash pandya 5times
	{
		LCD_cmd(LCD_LINE2);
		LCD_str("      "); //6 spaces
		delay_ms(1000);
		
		LCD_cmd(LCD_LINE2);
		LCD_str("PANDYA");
		delay_ms(1000);
	}
	LCD_cmd(LCD_CLR);
	while(1);
	
}
