/*
   Display binary count of switch presses on 8 LEDs (LPC2138)
   P0.0–P0.3 : Active-LOW LEDs
   P0.4–P0.7 : Active-HIGH LEDs
   P0.16     : Active-LOW switch
   Count (0–255) shown in binary */

#include<LPC213x.h>
#include<stdint.h>
#include"macros.h"

int main(void)
{
	
	uint32_t count=0,binary;
	PINSEL0=0X00000000;
	CONFIG_GPIO_PIN(16);
	GPIO_OUTPUT_PINS(IODIR0,0XFF); //PO.0 TO P0.07 AS OUTPUT PINS
	GPIO_INPUT_PIN(IODIR0,16); // P0.16 TO INPUT PIN FOR SWITCH
	
	
	while(1)
	{
	
	if(AL_SW_PRESSED(0,16))
	{
        count++;
        while(AL_SW_PRESSED(0,16));
	}
		
		if(count>255)
		count=0;
		
		binary=(count&0XF0)|(~count&0X0F);
		IOPIN0=(IOPIN0&~0XFF)|(binary);
	
	}
			
}


