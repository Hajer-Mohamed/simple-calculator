/*
 * LCD.h
 *
 * Created: 8/19/2024 6:26:36 PM
 *  Author: elsawah
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "DIO.h"
#include "LCD_config.h"
#define CLR_SCREEN 0x01
#define CURSOR_ON_DISPLAY_ON 0x0e
#define ENTY_MODE 0x06
#define RETURN_HOME 0x06;
#if defined four_bits_mode
#define EN 0
#define RS 1
#define RW 2
#define FOUR_BITS 0x28
#elif defined eight_bits_mode
#define EN 0
#define RS 1
#define RW 2
#define EIGHT_BITS 0x38
#endif 

#define lcd_data_port 'A'
#define lcd_control_port 'B'

void LCD_init(void);
static void enable(void);
void LCD_SEND_CMD(char cmd);

void LCD_SEND_CHAR(char data);

void LCD_SEND_STRING(char *data);
void LCD_clearscreen();
void LCD_MOVE_CURSOR(char row , char col);






#endif /* LCD_H_ */