/*
   2-Digit Multiplexed 7-Segment Counter (00–99)

   LPC2138 (ARM7) is used to display numbers from 00 to 99
   on two Common Cathode 7-segment displays.

   - Multiplexing 
   - Timer0 is configured for 1ms hardware polling delay.
   - Each number is displayed for approximately 1 second.

   P0.0–P0.7  Segment lines
   P0.8       Tens digit
   P0.9       Units digit
*/


#include <LPC213x.h>
#include <stdint.h>
#include "macros.h"

#define SEG_MASK 0XFF
#define DIG1 8
#define DIG2 9

/*void delay_ms(uint32_t dlyMs)
{
	uint32_t i;
	for(i=0;i<4000*dlyMs;i++);
}*/

unsigned char segLUT[10]=
{0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};

void timer0_init_1ms(void)
{
    T0TCR = 0x02;        // Reset Timer
    T0PR  = 14999;       // 1 ms tick (PCLK = 15 MHz)
    T0MR0 = 1;           // Match every 1 ms
    T0MCR = 0x03;        // Interrupt + Reset on match
    T0TCR = 0x01;        // Start Timer
}

void delay_ms_timer(uint32_t ms)
{
    uint32_t count = 0;

    while(count < ms)
    {
        if(T0IR & 0x01)
        {
            T0IR = 0x01;  // Clear match flag
            count++;
        }
    }
}


int main(void)
{
	int32_t i,j;
	PINSEL0&=~0X000FFFFF; //P0.0 TO P0.9 AS GPIO
	GPIO_OUTPUT_PINS(IODIR0,0X3FF); //OUTPUT PINS
	timer0_init_1ms();
	while(1)
	{
		for(i=0;i<100;i++)
		{
			for(j=0;j<=250;j++)
			{
				IOCLR0=(1<<DIG1)|(1<<DIG2); //disable digits
				IOCLR0=SEG_MASK; //clear segments
				IOSET0=segLUT[i/10];//load data
				IOSET0=(1<<DIG1); //enable digit
				delay_ms_timer(1);
				//IOCLR0=(1<<DIG1); //disable digit
				
				IOCLR0=(1<<DIG1)|(1<<DIG2); //disable digits
				IOCLR0=SEG_MASK; //clear segments
				IOSET0=segLUT[i%10];//load data
				IOSET0=(1<<DIG2); //enable digit
				delay_ms_timer(1);
				
				//IOCLR0=(1<<DIG2); //disable digit
				
			}
		}
	}
}

