/*
  Switch-Based Word Capitalization using 16x2 LCD

	- SW1 On pressn   "hardik pandya"
				On release  "Hardik Pandya"
				
	- SW2 On press    "rohith sharma"
				On release  "Rohith Sharma"
				
	- Display "waiting for input" initially.
*/


#include <LPC213x.h>
#include "lcd.h"
#include "macros.h"

#define SW1 1  //P0.1
#define SW2 2  //P0.2

char str1[]="hardik pandya";
char str2[]="rohith sharma";

void copy_str(char dest[], char src[])
{
    int i=0;

    while(src[i]!='\0')
    {
        dest[i]=src[i];
        i++;
    }
    dest[i]='\0';
}

void capitalize(char str[])
{
	int i=0;
	if(str[0]>='a' && str[0]<='z')
		str[0]=str[0]-32;
	
	i=1;
	while(str[i]!='\0')
	{
		if(str[i-1]==' ' && str[i]>='a' && str[i]<='z')
			str[i]=str[i]-32;
		
		i++;
	}
}

int main(void)
{
	char temp[20];
	CONFIG_GPIO_PIN(SW1);
	CONFIG_GPIO_PIN(SW2);
	
	GPIO_INPUT_PIN(IODIR0,SW1);
	GPIO_INPUT_PIN(IODIR0,SW2);

	LCD_init();
	LCD_cmd(LCD_LINE1+5);
	LCD_str("WAITING");
	LCD_cmd(LCD_LINE2+4);
	LCD_str("FOR INPUT");
	while(1)
	{
		if(AL_SW_PRESSED(0,SW1))
		{
			delay_ms(20);
			if(AL_SW_PRESSED(0,SW1))
			{
				LCD_cmd(LCD_CLR);
				LCD_cmd(LCD_LINE1);
				LCD_str(str1);
				while(AL_SW_PRESSED(0,SW1));
				copy_str(temp,str1);
				capitalize(temp);
				LCD_cmd(LCD_LINE2);
				LCD_str(temp);
			}
		}
		
		else if(AL_SW_PRESSED(0,SW2))
		{
			delay_ms(20);
			if(AL_SW_PRESSED(0,SW2))
			{
				LCD_cmd(LCD_CLR);
				LCD_cmd(LCD_LINE1);
				LCD_str(str2);
				while(AL_SW_PRESSED(0,SW2));
				copy_str(temp,str2);
				capitalize(temp);
				LCD_cmd(LCD_LINE2);
				LCD_str(temp);
			}
		}
		
	}
}
