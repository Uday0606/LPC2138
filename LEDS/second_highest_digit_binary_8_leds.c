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
	
	result=((shigh&0X0F)<<4)| (~shigh&0x0F);
	IOPIN0=(IOPIN0&~0XFF)|(result);
  
	while(1);
}
