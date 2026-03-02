/*
  Dual External Interrupt Counter – LPC2138 (ARM7)
 
  - EINT0 (P0.1) increments counter
  - EINT1 (P0.3) decrements counter
  - Counter range: 0–15
  - Binary value displayed on P0.4–P0.7 (Active LOW LEDs)
 
  - VIC slot 0  EINT0 (higher priority)
  - VIC slot 1  EINT1 (lower priority)
 
 */

#include <LPC213x.h>
#include <stdint.h>
#include "macros.h"


volatile uint32_t count=0;
volatile uint8_t inc_flag=0;
volatile uint8_t dec_flag=0;

#define AL_LEDS 0XF0
void EINT0_ISR(void)__irq
{
	inc_flag=1;
	EXTINT=(1<<0); //clear EINT0 interrupt flag
	VICVectAddr=0;  //Ack interrupt to VIC
}

void EINT1_ISR(void)__irq
{
	dec_flag=1;
	EXTINT=(1<<1); //clear EINT1 interrupt flag
	VICVectAddr=0;  //Ack interrupt to VIC
}
int main(void)
{
	uint32_t value;
	CONFIG_PIN_FUNC(1,3); //EINT0 switch
	CONFIG_PIN_FUNC(3,3);  //EINT1 switch
	GPIO_OUTPUT_PINS(IODIR0,AL_LEDS);

	

	//EINT0
	EXTMODE|=(1<<0);//edge
	EXTPOLAR&=~(1<<0); //falling edge
	EXTINT=(1<<0);
	VICIntEnable|=(1<<14); //enable EINT0
	VICVectCntl0=(1<<5)|14; //slot+channel number 
	VICVectAddr0=(unsigned int)EINT0_ISR;//assign isr address
	
	//EINT1
	EXTMODE|=(1<<1);//edge
	EXTPOLAR&=~(1<<1); //falling edge
	EXTINT=(1<<1);
	VICIntEnable|=(1<<15); //enable EINT1
	VICVectCntl1=(1<<5)|15; //slot+channel number 
	VICVectAddr1=(unsigned int)EINT1_ISR;//assign isr address
	
	while(1)
	{
		if(inc_flag)
		{
			inc_flag=0;
			if(count<15)
			count++;
		}
		if(dec_flag)
		{
			dec_flag=0;
			if(count>0)
				count--;
		}
		IOPIN0=(IOPIN0&~0XF0)|((~count&0X0F)<<4);  //p0.4 to p0.7
	}
}
