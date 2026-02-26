#include <LPC213x.h>
#include "lcd.h"

void delay_ms(uint32_t dlyMs)
{
	uint32_t i;
	for(i=0;i<6000*dlyMs;i++);
}

// LCD COMMAND FUN
void LCD_cmd(uint8_t cmd)
{
	IOCLR0=(1<<RS_PIN); //RS=0 command
	IOCLR0=(1<<RW_PIN); //RW=0 write
	
	IOCLR0=DATA_MASK;  //clear P0.8 to P0.15
	IOSET0=(cmd<<DATA_SHIFT);//shift data to P0.8 to P0.15
	
	IOSET0=(1<<EN_PIN); //EN=1
	delay_ms(2);
	IOCLR0=(1<<EN_PIN); //EN=0
	
}

//LCD DATA FUN
void LCD_data(uint8_t data)
{
	IOSET0=(1<<RS_PIN); //RS=1
	IOCLR0=(1<<RW_PIN); //RW=0
	
	IOCLR0=DATA_MASK;
	IOSET0=(data<<DATA_SHIFT);
	
	IOSET0=(1<<EN_PIN); //EN=1;
	delay_ms(2);
	IOCLR0=(1<<EN_PIN); //EN=0;
}

//LCD INIT
void LCD_init(void)
{
	//configure pins as output
	IODIR0|=DATA_MASK;
	IODIR0|=(1<<RS_PIN)|(1<<RW_PIN)|(1<<EN_PIN);
	
	delay_ms(20); //power on delay
	LCD_cmd(0X30);
	delay_ms(5);
	
	LCD_cmd(0X30);
	delay_ms(1);
	LCD_cmd(0X30);
	
	LCD_cmd(0X38);
	LCD_cmd(0X08);
	LCD_cmd(0X01);
	delay_ms(2);
	
	LCD_cmd(0x06);
	LCD_cmd(0x0C);
}

// LCD STRING FUN
void LCD_str(const char *str)
{
	while(*str)
	{
		LCD_data(*str);
		str++;
	}
}

void LCD_int(int32_t num)
{
	char temp[10];
	int32_t i=0,j;
	
	//-ve numbers
	if(num<0)
	{
		LCD_data('-'); //minus sign
		num=-num; //make number +ve
	}
	//zero
	if(num==0)
	{
		LCD_data('0');
		return;
	}
	//convert dig to chars
	while(num>0)
	{
		temp[i++]=(num%10)+'0';
		num/=10;
	}
	//reverse & disp
	for(j=i-1;j>=0;j--)
	{
		LCD_data(temp[j]);
	}
}

void LCD_float( float fnum,uint32_t ndp)
{
	int32_t inum;
	
	if(fnum<0.0f)
	{
		LCD_data('-');
		fnum=-fnum;
	}
	inum=(int32_t)fnum;  //extract integer part
	LCD_int(inum);			 // display integer part

	if(ndp>0)
		LCD_data('.');
	
	while(ndp--)
	{
		fnum=(fnum-inum)*10.0f; //remove integer part & shift one decimal
		inum=(int32_t)fnum;    // extract next digit
		LCD_data(inum+ '0');   //convert dig to ASCII & display
	}
}

void LCD_custom_char(uint8_t location,uint8_t *pattern)
{
	uint8_t i;
	
	location &=0X07;   //limit location to 0-7
	LCD_cmd(LCD_CGRAM_START|(location<<3)); //set CGRAM address
	
	for(i=0;i<8;i++)
	{
		LCD_data(pattern[i]);
	}
	LCD_cmd(LCD_DDRAM_START); //return to DDRAM
}
	


	
	
