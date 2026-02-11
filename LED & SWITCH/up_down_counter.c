/*  Up/Down Counter using 2 Switches and 8 LEDs (LPC2138)
   SW1 (P0.16)  Increment
   SW2 (P0.17)  Decrement
   Count range: 0–255 (saturation logic applied)
   - At 0, decrement has no effect
   - At 255, increment has no effect
   P0.0–P0.3 : Active-LOW LEDs
   P0.4–P0.7 : Active-HIGH LEDs
   Binary count displayed using masking. */


#include<LPC213x.h>
#include<stdint.h>
#include"macros.h"

int main(void)
{
	uint32_t count=0,binary;
	PINSEL0=0X00000000; 
	CONFIG_GPIO_PIN(16); 
	CONFIG_GPIO_PIN(17); 
	
	GPIO_OUTPUT_PINS(IODIR0,0XFF); //LEDS
	GPIO_INPUT_PINS(IODIR0,(1<<16)|(1<<17));// SWITCHES
	
	while(1)
	{
		if(AL_SW_PRESSED(0,16))
		{
			if(count<255)
		      count++;
		 while(AL_SW_PRESSED(0,16));
		}
		else if(AL_SW_PRESSED(0,17))
		{
			if(count>0)
				  count--;
		 while(AL_SW_PRESSED(0,17));
		}

	binary=(count&0XF0)|(~count&0X0F);
	IOPIN0=(IOPIN0&~0XFF)|(binary);
	}
}
