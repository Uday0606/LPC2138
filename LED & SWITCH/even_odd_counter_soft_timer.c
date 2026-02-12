/*
   Even/Odd Counter using Software Timer (LPC2138)

   SW1 (P0.16)  Start EVEN sequence (0,2,4,.)
   SW2 (P0.17)  Start ODD sequence (1,3,5,.)
	 
   - Numbers increment every 1 second.
   - 1-second timing generated using 1 ms software time counter.
   - No blocking 1-second delay used.
        EVEN  restart from 0
        ODD   restart from 1
   LEDs:
   P0.0-P0.3  Active-LOW LEDs
   P0.4-P0.7  Active-HIGH LEDs
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
	uint32_t num=0,mode=0,binary,time=0;
	PINSEL0=0X00000000;
	CONFIG_GPIO_PIN(16);
	CONFIG_GPIO_PIN(17);
	
	GPIO_OUTPUT_PINS(IODIR0,0XFF); //LEDS
	GPIO_INPUT_PINS(IODIR0,(1<<16)|(1<<17)); //SWITCHES
	
	IOPIN0=(IOPIN0&~0XFF)|(0X0F); //ALL LEDS OF INITIALLY
	
	while(1)
	{
		if(AL_SW_PRESSED(0,16))
		{
			mode=1; //even
			num=0;
		}
		else if(AL_SW_PRESSED(0,17))
		{
			mode=2; //odd
			num=1;
		}
			delay_ms(1);
		  time++;
			if(time>=1000)
			{
				time=0;
		if(mode==1)
		{
			binary=(num&0XF0)|(~num&0X0F);
			IOPIN0=binary;
			
			
			num+=2;
			if(num>255)
				num=0;
		}
		 else if(mode==2)
		{
			binary=(num&0XF0)|(~num&0X0F);
			IOPIN0=binary;
			
			num+=2;
			if(num>255)
				num=1;
		}
	}
}
	}
