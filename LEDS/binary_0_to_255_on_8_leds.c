/*
 Displays the binary equivalent of numbers from 0 to 255 on 8 LEDs.
 P0.0–P0.3 : Active LOW LEDs
 P0.4–P0.7 : Active HIGH LEDs
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
	uint32_t i,binary_num;
	PINSEL0=0X00000000; //GPIO mode
	IODIR0|=0XFF; //set PO.0 to p0.07 as output pin
	
	/*initially all off*/
	IOSET0=0X0F; //active low leds off
	IOCLR0=0XF0; //active high leds off
	
	for(i=0;i<256;i++)
	{
		binary_num=(i&0xF0)|(~i&0x0F);
    IOCLR0=binary_num&0x0F;   // active low leds
		IOSET0=binary_num&0xF0;   // active high leds

		delay_ms(500);
	}
	while(1);
}
