/*
 * keypad_interface.c
 *
 * Created: 8/26/2024 4:28:33 PM
 *  Author: elsawah
 */ 

#include "keypad_driver.h"

void  keypad_init(void)
{
	set_pin_dir(keypad_port,0,1);
	set_pin_dir(keypad_port,1,1);
	set_pin_dir(keypad_port,2,1);
	set_pin_dir(keypad_port,3,1);
	
	set_pin_dir(keypad_port,4,0);
	set_pin_dir(keypad_port,5,0);
	set_pin_dir(keypad_port,6,0);
	set_pin_dir(keypad_port,7,0);
	
	DIO_vconnectpullup(keypad_port,4,1);
	DIO_vconnectpullup(keypad_port,5,1);
	DIO_vconnectpullup(keypad_port,6,1);
	DIO_vconnectpullup(keypad_port,7,1);
}

unsigned char keypad_check_press(void)
{
	unsigned char arr[4][4]={{'1','2','3','/'}, {'4','5','6','-'},{'7','8','9','+'},{'*','0','=','A'}};
	char row , col, x;
	char return_val=not_pressed;
	for(row=0;row<=3;row++)
	{
		DIO_write(keypad_port,0,1);
		DIO_write(keypad_port,1,1);
		DIO_write(keypad_port,2,1);
		DIO_write(keypad_port,3,1);
		
		DIO_write(keypad_port,row,0);
		for(col=0;col<=3;col++)
		{
			x=DIO_read(keypad_port,(col+4));
			if(x==0)
			{
				return_val=arr[row][col];
				break;
			}
		}
		if(x==0)
		{
			break;
		}
	}
	return return_val;
}