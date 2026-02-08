/*
  
  Switch ON LEDs one by one from right to left at 1 second rate.
  - P0.0 to P0.3 : Active LOW LEDs
  - P0.4 to P0.7 : Active HIGH LEDs
 */

#include<LPC213x.h>
#include<stdint.h>

void delay_ms(uint32_t dlyMs)
{
	uint32_t i;
	for(i=0;i<dlyMs*12000;i++);
}
int main(void)
{
	uint32_t i;
	PINSEL0 = 0x00000000;  // GPIO mode
	
		//IODIR0|=(1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7);  or
	IODIR0|=0XFF; //set PO.0 to p0.07 as output pin
	
	  IOSET0 = 0x0F;   // active-LOW LEDs OFF
    IOCLR0 = 0xF0;   // active-HIGH LEDs OFF

	while(1)
	{
	for(i=0;i<8;i++)
	{
		if(i<4) //active low leds
		{
			IOCLR0=(1<<i); //LED ON (active low)
			delay_ms(1000);
			IOSET0=(1<<i); //LED OFF
			delay_ms(1000);
		}
		else
		{
			IOSET0=(1<<i); // LED ON (active high)
			delay_ms(1000);
			IOCLR0=(1<<i); //LED OFF
			delay_ms(1000);
		}
	}
	}
	
}



