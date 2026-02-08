
/*
 Active High LED Blink
 An LED is connected to Port0 pin P0.5 in active-high configuration.
 The LED is turned ON and OFF with a delay of 1 second.
*/

#include<LPC213x.h>
#include<stdint.h>


void delay_s(uint32_t dlyS)
{
	uint32_t i;
	for( i=0;i<dlyS*12000000;i++);
}

int main(void)
{
	uint32_t i;
	IODIR0|=1<<5; //Set P0.05 as output pin
	
	
	for( i=0;i<10;i++)
	{
		IOSET0=1<<5;  //send logic 1 to P0.05  LED ON
		delay_s(1);
		IOCLR0=1<<5;   //send logic 0 to P0.05 LED OFF
		delay_s(1);
	}
	
	while(1); //End of program
  
	}



		

	 
