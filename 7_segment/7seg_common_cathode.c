/*
   LPC2138 - 7 Segment Display (Common Cathode)
 
  Displays digits 0–9 continuously on a single-digit
  7-segment display using software delay.
 
  Connections:
  P0.0–P0.6 -> a–g    //dp not used
	
  Segment Bit Mapping:
	bit0-bit6 ->a-g
	
  Common Cathode -> GND
  330R resistor per segment
	
 */

#include <LPC213x.h>
#include <stdint.h>
#include "macros.h"

unsigned char segLUT[10]=
{0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};

void delay_ms(uint32_t dlyMs)
{
	uint32_t i;
	for(i=0;i<4000*dlyMs;i++);
	
}
int main(void)
{
	uint32_t i;
	PINSEL0&=~(0X00003FFF);  //P0.0 TO P0.06
	GPIO_OUTPUT_PINS(IODIR0,0X7F);
	
	while(1)
	{
		for(i=0;i<10;i++)
		{
			IOPIN0=(IOPIN0&~0X7F)|(segLUT[i]);
			delay_ms(1000);
		}
		
	}
}
