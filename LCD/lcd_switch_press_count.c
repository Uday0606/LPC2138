/* Switch Press Counter using 16x2 LCD

Description:
  - Switch is connected to P0.1
  - On every valid press, counter increments
  - Debouncing is implemented to avoid multiple counts
  - LCD displays updated switch count on Line 2
*/

#include <LPC213x.h>
#include "lcd.h"
#include "macros.h"

#define SW 1  //switch connected to P0.1
int main(void)
{
	uint32_t count=0;
	CONFIG_GPIO_PIN(SW);
	GPIO_INPUT_PIN(IODIR0,SW);
	LCD_init();
	
	LCD_cmd(LCD_LINE1);
	LCD_str("Switch Count:");
	
	LCD_cmd(LCD_LINE2);
	LCD_int(count);
	
	while(1)
	{
		if(AL_SW_PRESSED(0,SW))
		{
			delay_ms(20); //debounce
			if(AL_SW_PRESSED(0,SW))
			{
				count++;
				while(AL_SW_PRESSED(0,SW)); //wait release
				
				LCD_cmd(LCD_LINE2);
				LCD_str("      ");
				
				LCD_cmd(LCD_LINE2);
				LCD_int(count);
				
			}
		}
	}
}
