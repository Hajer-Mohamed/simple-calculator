/*
 * LCD.c
 *
 * Created: 8/19/2024 6:27:59 PM
 *  Author: elsawah
 */ 

#include "LCD.h"
#define F_CPU 8000000UL
#include <util/delay.h>

void LCD_init(void)
{
	_delay_ms(200);
	#if defined eight_bits_mode
	set_pin_dir(lcd_data_port,0,1);
	set_pin_dir(lcd_data_port,1,1);
	set_pin_dir(lcd_data_port,2,1);
	set_pin_dir(lcd_data_port,3,1);
	set_pin_dir(lcd_data_port,4,1);
	set_pin_dir(lcd_data_port,5,1);
	set_pin_dir(lcd_data_port,6,1);
	set_pin_dir(lcd_data_port,7,1);
	set_pin_dir(lcd_control_port,EN,1);
	set_pin_dir(lcd_control_port,RW,1);
	set_pin_dir(lcd_control_port,RS,1);
	DIO_write(lcd_control_port,RW,0);
	LCD_SEND_CMD(EIGHT_BITS);
	_delay_ms(1);
	LCD_SEND_CMD(CURSOR_ON_DISPLAY_ON); 
	_delay_ms(1);
	LCD_SEND_CMD(CLR_SCREEN);
	_delay_ms(10);
	LCD_SEND_CMD(ENTY_MODE);
	_delay_ms(1);
	
	#elif defined four_bit_mode
	set_pin_dir(lcd_data_port,4,1);
	set_pin_dir(lcd_data_port,5,1);
	set_pin_dir(lcd_data_port,6,1);
	set_pin_dir(lcd_data_port,7,1);
	set_pin_dir(lcd_control_port,EN,1);
	set_pin_dir(lcd_control_port,RW,1);
	set_pin_dir(lcd_control_port,RS,1);
	DIO_write(lcd_control_port,RW,0);
	LCD_SEND_CMD(RETURN_HOME);
	_delay_ms(10);
	LCD_SEND_CMD(FOUR_BITS);
	_delay_ms(1);
	LCD_SEND_CMD(CURSOR_ON_DISPLAY_ON);
	_delay_ms(1);
	LCD_SEND_CMD(CLR_SCREEN);
	_delay_ms(10);
	LCD_SEND_CMD(ENTY_MODE);
	_delay_ms(1);
	#endif
}

static void enable(void)
{
	DIO_write(lcd_control_port,EN,1);
	_delay_ms(2);
	DIO_write(lcd_control_port,EN,0);
	_delay_ms(2);
}

void LCD_SEND_CMD(char cmd)
{
	#if defined eight_bits_mode
	DIO_write_port(lcd_data_port,cmd);
	DIO_write(lcd_control_port,RS,0);
	enable();
	
	#elif defined four_bits_mode
	write_high_nibble(lcd_data_port,cmd>>4);
	DIO_write(lcd_control_port,RS,0);
	enable();
	write_high_nibble(lcd_data_port,cmd);
	DIO_write(lcd_control_port,RS, 0);
	enable();
	_delay_ms(1);
	#endif
	_delay_ms(1);
}


void LCD_SEND_CHAR(char data)
{
	#if defined eight_bits_mode
	DIO_write_port(lcd_data_port,data);
	DIO_write(lcd_control_port,RS,1);
	enable();
	
	#elif defined four_bits_mode
	write_high_nibble(lcd_data_port,data>>4);
	DIO_write(lcd_control_port,RS,1);
	enable();
	write_high_nibble(lcd_data_port,data);
	DIO_write(lcd_control_port,RS, 1);
	enable();
	_delay_ms(1);
	#endif

	_delay_ms(1);
}

void LCD_SEND_STRING(char *data)
{
	while((*data)!='\0')
	{
		LCD_SEND_CHAR(*data);
		data++;
	}
}

void LCD_clearscreen()
{
	LCD_SEND_CMD(CLR_SCREEN);
	_delay_ms(10);
}

void LCD_MOVE_CURSOR(char row , char col)
{
	char data;
	if(row<1 || row>2 || col<1 || col>16)
	{
		data=0x80;
	}
	else if(row==1)
	{
		data=0x80+col-1;
	}
	else if(row==2)
	{
		data=0xc0+col-1;
	}
	LCD_SEND_CMD(data);
	_delay_ms(1);
}
