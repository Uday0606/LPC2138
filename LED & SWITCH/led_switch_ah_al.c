/*
  Program: 8 LEDs (4 active-high, 4 active-low) controlled by
           4 active-low switches using LPC213x GPIO.
 
  Switches : P0.16 – P0.19 (active-low)
  LEDs     : P0.0 – P0.3  (active-low)
             P0.4 – P0.7  (active-high)
 

  SW1 -> LED0 & LED7
  SW2 -> LED1 & LED6
  SW3 -> LED2 & LED5
  SW4 -> LED3 & LED4
 */

#include<LPC213x.h>
#include<stdint.h>
#include "macros.h"

#define SW1 16
#define SW2 17
#define SW3 18
#define SW4 19
void delay_ms(uint32_t dlyMs)
{
	uint32_t i;
	for(i=0;i<dlyMs*12000;i++);
}

int main(void)
{
	PINSEL0=0X00000000; //GPIO
	GPIO_OUTPUT_PINS(IODIR0,0XFF);      //or IODIR0|=0XFF, SET PO.0 TO P0.07 AS OUTPUT PINS FOR LEDS
	GPIO_INPUT_PINS(IODIR0,0X000F0000); //or IODIR0&=~(0X000F0000) SET P0.16 TO P0.19 AS INPUT PINS FOR LOW SWITCHES
	/*INITIALLY ALL OFF*/
		IOSET0=0X0F; //AL_LEDS
		IOCLR0=0XF0; //AH_LEDS


	while(1)
	{
		
	if(AL_SW_PRESSED(0,SW1))  // AL_SWITCH
	{
		LED_AL_ON(0,0);
		LED_AH_ON(0,7);
	}		
	else if(AL_SW_PRESSED(0,SW2))
	{
		LED_AL_ON(0,1);
		LED_AH_ON(0,6);
	}
	else if(AL_SW_PRESSED(0,SW3))
	{
		LED_AL_ON(0,2);
		LED_AH_ON(0,5);
	}
	else if(AL_SW_PRESSED(0,SW4))
	{
		LED_AL_ON(0,3);
		LED_AH_ON(0,4);
	}
  }
}
