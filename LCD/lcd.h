#ifndef LCD_H
#define LCD_H

#include <stdint.h>
void delay_ms(uint32_t dlyMs);
void LCD_cmd(uint8_t cmd);
void LCD_data(uint8_t data);
void LCD_init(void);
void LCD_str(const char *str);
void LCD_int(int32_t num);
void LCD_float(float fnum,uint32_t ndp);
void LCD_custom_char(uint8_t location,uint8_t *pattern);

//LCD COMMANDS
/*-------------BASIC COMMANDS-------------*/
#define LCD_CLR 			 				 0X01   // clears ddram cur pos 0
#define LCD_RTN_HOME   				 0x02   //cursor pos 0

/*-------------ENTRY MODE---------------*/
#define  LCD_ENTRY_LEFT				 0X04  //cursor moves left after write
#define	 LCD_ENTRY_RIGHT			 0X06  //cursor moves right after write
#define	 LCD_ENTRY_LEFT_SHIFT  0X05  //cursor left + display shift
#define	 LCD_ENTRY_RIGHT_SHIFT 0X07  //cursor right + display shift


/*----------------DISPLAY CONTROL--------------*/
#define LCD_DISP_OFF		       0X08
#define LCD_DISP_OFF_CUR_ON    0X0A
#define LCD_DISP_ON				     0X0C
#define LCD_DISP_ON_CUR_ON     0X0E
#define LCD_DISP_ON_CUR_BLINK  0X0F

/*--------------CURSOR DISPLAY SHIFT------------*/
#define LCD_CUR_LEFT		  		 0X10
#define LCD_CUR_RIGHT		 			 0X14
#define SHIFT_DISP_LEFT				 0X18
#define SHIFT_DISP_RIGHT			 0X1C

/*----------CURSOR POSITION-----------*/
#define LCD_LINE1							 0X80
#define LCD_LINE2							 0XC0

/*-----------FUNCTION SET-------------*/
#define LCD_8BIT_1LINE				 0X30
#define LCD_8BIT_2LINE				 0X38

/*-----------MEMORY ADDRESS COMMANDS-----------*/
#define LCD_CGRAM_START 			 0x40
#define LCD_DDRAM_START 			 0x80

//PIN CONFIGURATION
#define RS_PIN 4
#define RW_PIN 5
#define DATA_SHIFT 8
#define DATA_MASK (0XFF<<DATA_SHIFT)
#define EN_PIN 6

#endif

