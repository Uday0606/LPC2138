/*
   LPC2138 - 7 Segment Display (Common Anode)
 
  Displays digits 0–9 continuously on a single-digit
  7-segment display using software delay.
 
  Connections:
  P0.0–P0.6 -> a–g    //dp not used
	
  Segment Bit Mapping:
	bit0-bit6 ->a-g
	
  Common Anode -> VCC
  330R resistor per segment
	
 */

#include <LPC213x.h>
#include <stdint.h>
#include "macros.h"

unsigned char segLUT[10]=
{0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90};

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
