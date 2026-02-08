
/*
	8 LED’s (4-active high and 4-active low) connected to port0 (0.0
   0.7) in the given pattern.  
	a. First all LEDs should be OFF, at 1st second, LED 0 and LED 7 (P0.0 and 
	P0.7) should be ON 
	b. At 2nd second, LED 1 and LED 6 (P0.1 and P0.6) should be ON   
	c. At 3rd second, LED 2 and LED 5 (P0.2 and P0.5) should be ON  
	d. At 4th second, LED 3 and LED 4 (P0.3 and P0.4) should be ON 
	e. Repeat above pattern for 5 times and stop the process. */
	
#include<LPC213x.h>
#include<stdint.h>

void delay_ms(uint32_t dlyMs)
{
	uint32_t i;
	for(i=0;i<dlyMs*12000;i++);
}

int main(void)
{

	uint32_t i,j,times=5;
	PINSEL0=0X00000000; //GPIO MODE
	
	IODIR0|=0XFF; // set PO.0 to p0.07 as output pin
	
	/*initially all off*/
	IOSET0=0X0F; //active low leds off
	IOCLR0=0XF0; //active high leds off 
	
	while(times)
	{
	for(i=0,j=7;i<j;i++,j--)
	{
		IOCLR0=(1<<i); //active low led on
		IOSET0=(1<<j); // active high led on
		delay_ms(1000);
		IOSET0=(1<<i); // active low led off
		IOCLR0=(1<<j); // active high led off
	}
	times--;
  }
	while(1); //end of program
}
