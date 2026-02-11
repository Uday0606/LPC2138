/* 
    Up/Down Counter using 2 Active-Low Switches (LPC2138)

   SW1 (P0.16)  Increment count continuously (1 step per second)
   SW2 (P0.17)  Decrement count continuously (1 step per second)

   - Counting continues as long as the respective switch is held.
   - If both switches are pressed simultaneously, no operation is performed.
   - Count range: 0–255 (saturation logic applied)
         At 0    Decrement has no effect
         At 255  Increment has no effect

   LEDs:
   P0.0–P0.3  Active-LOW LEDs
   P0.4–P0.7  Active-HIGH LEDs
*/

#include<LPC213x.h>
#include<stdint.h>
#include"macros.h"

void delay_ms(uint32_t dlyMs)
{
	uint32_t i;
	for(i=0;i<4000*dlyMs;i++);
}
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
		while((AL_SW_PRESSED(0,16))&& (!(AL_SW_PRESSED(0,17))))
		{ 
			
			if(count<255)
		      count++;
			delay_ms(1000); // 1-second 

			
		}
		while((AL_SW_PRESSED(0,17)) && (!(AL_SW_PRESSED(0,16))))
		{
			
			if(count>0)
				  count--;
					delay_ms(1000);
		}
		
	binary=(count&0XF0)|(~count&0X0F);
	IOPIN0=(IOPIN0&~0XFF)|(binary);
	}
}
