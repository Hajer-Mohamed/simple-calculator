/*
 * IncFile1.h
 *
 * Created: 8/26/2024 4:28:42 PM
 *  Author: elsawah
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_


#define not_pressed 0xff
#define keypad_port 'D'

void  keypad_init(void);
unsigned char keypad_check_press(void);


#endif /* INCFILE1_H_ */