/* find the second highest digit in integer and display its binary 
   equivalent on 8-LEDS (4-Active High LEDS & 4-Active Low LEDS)*/
	 
#include<LPC213x.h>
#include<stdint.h>

void delay_ms(uint32_t dlyMs)
{
	uint32_t i;
	for(i=0;i<dlyMs*12000;i++);
}

int main(void)
{
	uint32_t num=1234,high=0,shigh=0,digit,result;
	PINSEL0=0X00000000;
	IODIR0|=0XFF; //set PO.0 to p0.07 as output pin
	
	/*initially all off*/
	IOSET0=0X0F; //active low leds off
	IOCLR0=0XF0; //active high leds off
	
	while(num)
	{
		digit=num%10; // extract last digit
		if(digit>high)
		{
			shigh=high;
			high=digit;
		}
		else if(digit>shigh && digit!=high)
		{
			shigh=digit;
		}
		num/=10; 
	}
	
	result=(shigh&0XF0)| (~shigh&0x0F);
	IOCLR0 = result & 0x0F;   // active low leds on
	IOSET0 = result & 0xF0;   // active high leds on
  
	while(1);
}
