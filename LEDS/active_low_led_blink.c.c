/*
 Active Low LED Blink
 An LED connected to P0.4 in active-low configuration is blinked
 with a 1-second delay. The LED blinks 5 times and then stops.
*/
#include<LPC213x.h>
#include<stdint.h>

void delay_s(uint32_t dlyS)
{
	uint32_t i;
	for(i=0;i<dlyS*12000000;i++);
}

int main(void)
{
	uint32_t i;
	IODIR0|=(1<<4); //set PO.04 as output pin
	
	for(i=0;i<5;i++)
	{
		IOCLR0=(1<<4); // LED ON (active LOW)
		delay_s(1);
		IOSET0=(1<<4);  // LED OFF
		delay_s(1);
	}
	while(1);

}
