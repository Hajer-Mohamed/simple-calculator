/*
 * simple_calculator.c
 *
 * Created: 9/19/2024 3:47:02 PM
 *  Author: elsawah
 */ 


#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "keypad_driver.h"
#include "LCD.h"
int main(void)
{
	label: LCD_init();
	keypad_init();
	unsigned char arr[6]={not_pressed,not_pressed,not_pressed,not_pressed,not_pressed,not_pressed};
	unsigned short result;
	unsigned char counter=0;
    while(1)
    {
       do
	   {
		   arr[counter]=keypad_check_press();
		   
	   }while(arr[counter]==not_pressed);
	   if(arr[counter]=='A' || arr[counter]=='=' ||arr[counter]=='+' ||arr[counter]=='-' ||arr[counter]=='/' ||arr[counter]=='*')
	   {
			LCD_clearscreen();
			goto label; 
	   }
	   else
	   {
		   LCD_SEND_CHAR(arr[counter]);
	   }
	   counter++;
	   _delay_ms(500);  
	   
	   do 
	   {
		   arr[counter]=keypad_check_press();
		   
	   } while (arr[counter]==not_pressed);
	   if(arr[counter]=='A' || arr[counter]=='=')
	   {
		   LCD_clearscreen();
		   goto label;
	   }		
	   else
	   {
		   LCD_SEND_CHAR(arr[counter]);
	   }		
	   counter++;
	   _delay_ms(500);
	   do 
	   {
		   arr[counter]=keypad_check_press();
		   
	   } while (arr[counter]==not_pressed);
	   if(arr[counter]=='A' || arr[counter]=='=' ||arr[counter]=='+' ||arr[counter]=='-' ||arr[counter]=='/' ||arr[counter]=='*')
	   {
		   LCD_clearscreen();
		   goto label;
	   }		
	   else
	   {
		   LCD_SEND_CHAR(arr[counter]);
	   }	
	   counter++;
	   _delay_ms(500);
	   
	   do 
	   {
		   arr[counter]=keypad_check_press();
	   } while (arr[counter]==not_pressed);
	   if(arr[counter]=='=')
	   {
		   LCD_SEND_CHAR(arr[counter]);
		   
		   switch(arr[counter-2])
		   {
			   case '+':
			   result=(arr[counter-3]-48)+(arr[counter-1]-48);
			   if(result>=100&&result<1000)
			   {
				   LCD_SEND_CHAR((result/100)+48);
					LCD_SEND_CHAR((result/10)%10+48);
					LCD_SEND_CHAR((result%10)+48);
			   }
			   else if(result>=10&&result<100)
			   {
				   LCD_SEND_CHAR((result/10)+48);
				   LCD_SEND_CHAR((result%10)+48);
			   }
			   else if(result <10)
			   {
				   LCD_SEND_CHAR((result)+48);
			   }
			   break;
			   
			   case '-':
			   result=(arr[counter-3]-48)-(arr[counter-1]-48);
			   if(result>=100&&result<1000)
			   {
				   LCD_SEND_CHAR((result/100)+48);
				   LCD_SEND_CHAR((result/10)%10+48);
				   LCD_SEND_CHAR((result%10)+48);
			   }
			   else if(result>=10&&result<100)
			   {
				   LCD_SEND_CHAR((result/10)+48);
				   LCD_SEND_CHAR((result%10)+48);
			   }
			   else if(result <10)
			   {
				   LCD_SEND_CHAR((result)+48);
			   }
			   break;
			   case '*':
			   result=(arr[counter-3]-48)*(arr[counter-1]-48);
			   if(result>=1000&&result<10000)
			   {
				   LCD_SEND_CHAR((result/1000)+48);
				   LCD_SEND_CHAR((result/100)%10+48);
				   LCD_SEND_CHAR((result/10)%10+48);
				   LCD_SEND_CHAR((result%10)+48);
			   }
			   else if(result>=100&&result<100)
			   {
				   LCD_SEND_CHAR((result/100)+48);
				   LCD_SEND_CHAR((result/10)%10+48);
				   LCD_SEND_CHAR((result%10)+48);
			   }
			   else if (result>=10&&result<100)
			   {
				   LCD_SEND_CHAR((result/10)+48);
				   LCD_SEND_CHAR((result%10)+48);
			   }
			   else if(result <10)
			   {
				   LCD_SEND_CHAR((result)+48);
			   }
			   break;
			   
			   case '/':
			   result=(arr[counter-3]-48)/(arr[counter-1]-48);
			   if(result>=100&&result<1000)
			   {
				   LCD_SEND_CHAR((result/100)+48);
				   LCD_SEND_CHAR((result/10)%10+48);
				   LCD_SEND_CHAR((result%10)+48);
			   }
			   else if(result>=10&&result<100)
			   {
				   LCD_SEND_CHAR((result/10)+48);
				   LCD_SEND_CHAR((result%10)+48);
			   }
			   else if(result <10)
			   {
				   LCD_SEND_CHAR((result)+48);
			   }
			   break;
			   default: break;
		   
		   }	       
    
	   }
	 else{
		   LCD_clearscreen();
		   goto label;
	 }
	   _delay_ms(500);
}
	   }