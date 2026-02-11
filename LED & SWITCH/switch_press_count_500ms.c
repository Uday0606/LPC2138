/* ECP: Count switch presses within 500 ms (LPC2138)
   P0.16 : Active-LOW switch
   P0.0–P0.3 : Active-LOW LEDs
   P0.4–P0.7 : Active-HIGH LEDs
   Time window starts after first press.
   Total presses within 500 ms displayed in binary. */

#include <LPC213X.h>
#include <stdint.h>
#include "macros.h"

void delay_ms(uint32_t dlyMs)
{
	uint32_t i;
	for(i=0;i<dlyMs*12000;i++);
}
int main(void)
{
	int32_t count=0,i,binary;
	PINSEL0=0X00000000;
	CONFIG_GPIO_PIN(16);
	GPIO_OUTPUT_PINS(IODIR0,0XFF); //PO.0 TO P0.07 AS OUTPUT PINS
	GPIO_INPUT_PIN(IODIR0,16); // P0.16 TO INPUT PIN FOR SWITCH
	
 IOPIN0=(IOPIN0 & ~0xFF)|(0x0F); //OFF LEDS

 while(1)
{
	if(AL_SW_PRESSED(0,16))
	{
		count=0;
		for(i=0;i<500;i++)
		{
			if(AL_SW_PRESSED(0,16))
				{	
					while(AL_SW_PRESSED(0,16));
						count++;
				}
				
				delay_ms(1);
		}
		binary=(count&0XF0)|(~count&0X0F);
		IOPIN0=(IOPIN0&~0XFF)|(binary);		
	}
	
}
}
