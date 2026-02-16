/*
 Display numbers 0–9 on two 7-segment displays ~1 second delay.

Even numbers are displayed on Segment 1 (DIG1).
Odd numbers are displayed on Segment 2 (DIG2).

Only one digit is active at a time.
Segments: P0.0–P0.7
DIG1: P0.8
DIG2: P0.9
*/

#include <LPC213x.h>
#include <stdint.h>
#include "macros.h"


#define SEG_MASK 0XFF
#define DIG1 8
#define DIG2 9

void delay_ms(uint32_t dlyMs)
{
	uint32_t i;
	for(i=0;i<4000*dlyMs;i++);
}

unsigned char segLUT[10]=
{0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};

int main(void)
{
	int32_t i;
	PINSEL0&=~0X000FFFFF; //P0.0 TO P0.9 AS GPIO
	GPIO_OUTPUT_PINS(IODIR0,0X3FF); //OUTPUT PINS
	
	while(1)
	{
		for(i=0;i<10;i++)
		{
			IOCLR0=(1<<DIG1)|(1<<DIG2); //clear digits
			IOCLR0=SEG_MASK; //clear segments
			IOSET0=segLUT[i]; //load number
			if(i%2==0)
			{
				IOSET0=(1<<DIG1); //even, enable digit 
				delay_ms(1000);
				IOCLR0=(1<<DIG1); //disable digit
			}
			else
			{
				IOSET0=(1<<DIG2); //odd, enable digit
				delay_ms(1000);
				IOCLR0=(1<<DIG2); //disable digit
			}
		}		
	}	
}
