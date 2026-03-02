/*
 External Interrupt Control – LPC2138 (ARM7)
 

  - EINT0 (P0.1)   Toggle LED1 (P0.10)
  - EINT1 (P0.3)   Toggle LED2 (P0.11)
  - EINT2 (P0.7)   Toggle LED3 (P0.12)
  - EINT3 (P0.9)   Toggle LED4 (P0.13)
 
  Hardware:
  - LEDs connected to P0.10–P0.13 (Active LOW)
  - Switches connected to EINT0–EINT3 pins
 
  Interrupt Configuration:
  - Edge-triggered (Falling Edge)
  - VIC Slot 0  EINT0 (Highest Priority)
  - VIC Slot 1  EINT1
  - VIC Slot 2  EINT2
  - VIC Slot 3  EINT3
  - Independent LED toggle per interrupt

*/


#include <LPC213x.h>
#include <stdint.h>
#include "macros.h"


/*ALL ACTIVE LOW_LEDS P0.10 TO P0.13*/
#define 	LED_1 10
#define 	LED_2 11
#define 	LED_3 12
#define 	LED_4 13


void EINT0_ISR(void)__irq
{
	IOPIN0^=(1<<LED_1);
	EXTINT=(1<<0); //clear EINT0 interrupt flag
	VICVectAddr=0;  //Ack interrupt to VIC
}
void EINT1_ISR(void)__irq
{
	IOPIN0^=(1<<LED_2);
	EXTINT=(1<<1); //clear EINT1 interrupt flag
	VICVectAddr=0;  //Ack interrupt to VIC
}
void EINT2_ISR(void)__irq
{
	IOPIN0^=(1<<LED_3);
	EXTINT=(1<<2); //clear EINT2 interrupt flag
	VICVectAddr=0;  //Ack interrupt to VIC
}
void EINT3_ISR(void)__irq
{
	IOPIN0^=(1<<LED_4);
	EXTINT=(1<<3); //clear EINT3 interrupt flag
	VICVectAddr=0;  //Ack interrupt to VIC
}

int main(void)
{
	CONFIG_PIN_FUNC(1,3); //EINT0 switch
	CONFIG_PIN_FUNC(3,3); //EINT1 switch
	CONFIG_PIN_FUNC(7,3); //EINT2 switch
	CONFIG_PIN_FUNC(9,3); //EINT3 switch
	 
	GPIO_OUTPUT_PINS(IODIR0,(1<<LED_1)|(1<<LED_2)|(1<<LED_3)|(1<<LED_4)); //AL_LEDS P0.10 TO P0.13
	IOSET0=((1<<LED_1)|(1<<LED_2)|(1<<LED_3)|(1<<LED_4)); //AL_LEDS OFF INTIALLY
	
	//EINT0
	EXTMODE|=(1<<0);//edge
	EXTPOLAR&=~(1<<0); //falling edge
	EXTINT=(1<<0);
	VICIntEnable|=(1<<14); //enable EINT0
	VICVectCntl0=(1<<5)|14; //slot0+channel number 
	VICVectAddr0=(unsigned int)EINT0_ISR;//assign isr address
	
	//EINT1
	EXTMODE|=(1<<1);//edge
	EXTPOLAR&=~(1<<1); //falling edge
	EXTINT=(1<<1);
	VICIntEnable|=(1<<15); //enable EINT1
	VICVectCntl1=(1<<5)|15; //slot1+channel number 
	VICVectAddr1=(unsigned int)EINT1_ISR;//assign isr address
	
	//EINT2
	EXTMODE|=(1<<2);//edge
	EXTPOLAR&=~(1<<2); //falling edge
	EXTINT=(1<<2);
	VICIntEnable|=(1<<16); //enable EINT2
	VICVectCntl2=(1<<5)|16; //slot2+channel number 
	VICVectAddr2=(unsigned int)EINT2_ISR;//assign isr address
	
	//EINT3
	EXTMODE|=(1<<3);//edge
	EXTPOLAR&=~(1<<3); //falling edge
	EXTINT=(1<<3);
	VICIntEnable|=(1<<17); //enable EINT3
	VICVectCntl3=(1<<5)|17; //slot3+channel number 
	VICVectAddr3=(unsigned int)EINT3_ISR;//assign isr address
	
	while(1)
	{
		
  }
}


