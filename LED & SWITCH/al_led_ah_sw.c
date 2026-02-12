/*
  Blink Active-Low LED using Active-High Switch
  P0.0   LED (Active-Low)
  P0.16  Switch (Active-High)
  On switch press, LED blinks 5 times.
 */

#include <LPC213x.h>
#include <stdint.h>
#include "macros.h"

void delay_ms(uint32_t dlyMs)
{
	uint32_t i;
	for(i=0;i<4000*dlyMs;i++);
}


int main(void)
{
	uint32_t i;
	CONFIG_GPIO_PIN(0);
	CONFIG_GPIO_PIN(16);
	
	GPIO_OUTPUT_PIN(IODIR0,0); //AL_LED
	GPIO_INPUT_PIN(IODIR0,16); //AH_SWITCH
	
	LED_AL_OFF(0,0); //AL OFF initially
	while(1)
	{
	if(AH_SW_PRESSED(0,16))
	{
		
	   for(i=0;i<5;i++)
		{
			LED_AL_ON(0,0); //AL ON
			delay_ms(1000);
			LED_AL_OFF(0,0); //AL OFF
			delay_ms(1000);
	  }
	} 
}
}
