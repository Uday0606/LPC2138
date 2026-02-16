/*
 Up–Down Counter using two 7-segment displays (Common Cathode)

- P0.0–P0.7  Segment lines
- P0.8  DIG1
- P0.9  DIG2

Displays 0–9 (up count) on DIG1 and then 9–0 (down count) on DIG2.
Each number is shown for approximately 1 second.
Only one digit is active at a time (no multiplexing).
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
			IOCLR0=SEG_MASK; //CLEAR SEGMENTS
			IOSET0=segLUT[i]; //LOAD NUMBER
			IOSET0=(1U<<DIG1); //ENABLE DIGIT
			delay_ms(1000);
			IOCLR0=(1U<<DIG1); //DISABLE DIGIT
		}
		for(i=9;i>=0;i--)
		{
			IOCLR0=SEG_MASK; //CLEAR SEGMENTS
			IOSET0=segLUT[i]; //LOAD NUMBER
			IOSET0=(1U<<DIG2); //ENABLE DIGIT
			delay_ms(1000);
			IOCLR0=(1U<<DIG2); //DISABLE DIGIT
		}
	}
}
