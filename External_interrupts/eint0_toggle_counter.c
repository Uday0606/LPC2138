/*
  Project: LPC2138 External Interrupt (EINT0)
 
  - P0.1 configured as EINT0 (falling edge trigger)
  - P0.0 used as active-low LED output
  - Each button press generates an interrupt
  - ISR sets a flag 
  - Main loop increments counter and controls LED
  - After 5 presses, LED remains permanently ON
 
 
 ******************************************************************************/

#include <LPC213x.h>
#include <stdint.h>
#include "macros.h"

volatile uint32_t count=0;
volatile uint8_t event_flag=0;
void EINT0_ISR(void)__irq
{
	event_flag=1;
	EXTINT=(1<<0); //clear EINT0 interrupt flag
	VICVectAddr=0;  //Ack interrupt to VIC
}
int main(void)
{
	CONFIG_PIN_FUNC(1,3); //EINT0 switch
	CONFIG_PIN_FUNC(0,0); //led
	GPIO_OUTPUT_PIN(IODIR0,0); //for led
	IOSET0=(1<<0);//Intially AL_LED OFF
	
	EXTMODE|=(1<<0);//edge
	EXTPOLAR&=~(1<<0); //falling edge
	EXTINT=(1<<0);
	VICIntEnable|=(1<<14); //enable EINT0
	VICVectCntl0=(1<<5)|14; //slot+channel number 
	VICVectAddr0=(unsigned int)EINT0_ISR;//assign isr address
	
	while(1)
	{
		if(event_flag)
		{
				event_flag=0;
				count++;
			if(count<5)
			{
				IO0PIN^=(1<<0); //TOGGLE led p0.0
			}
			else
			{
				IOCLR0=(1<<0); //AL_LED ON
			}
		}
	}
}
