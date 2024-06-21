/*
 * displayer.c
 *
 *  Created on: Nov 3, 2023
 *      Author: Ahmedmohamed
 */
#include"gpio.h"
#include"displayer.h"
#include"LCD.h"
#include"UART.h"
#include"keypad_flasha.h"
#include <util/delay.h> /* For the delay functions */
/*uint8 spass[5]={0};
uint8 thpass[5]={0};
uint8 reset_pass[5]={0};
uint8 i=0;
uint8 pass_state=0;
uint8  key=0;
uint8 fpass[5]={0};
uint8 counters=0;*/
/*void compare_tw0_passwords(void)
{
	while(1)
	{
		dis_pass1();
		display_firstpass();
		fpass[5]='#';
		i=0;
		reenter_pass();
		display_2ndpass();
		spass[5]='#';
		i=0;


		UART_Send_Byte(MC1_READY);//DEACTIVATE POLLING
		//sending pass1,pass2
		UART_Send_String(fpass);
		UART_Send_String(spass);
		if(UART_Receive_Byte()==1)
		{
			break;
		}
	}
}*/
void dis_pass1(void)
{
	LCD_ClearScreen();
	LCD_Displaystring("plz enter pass:");
	LCD_MoveCursor(1,0);
}
void reenter_pass(void)
{
	LCD_ClearScreen();
	LCD_Displaystring("plz renter the");
	LCD_MoveCursor(1,0);
	LCD_Displaystring("same pass:");
	LCD_MoveCursor(1,10);
}
void screen_door(void)
{
	LCD_ClearScreen();
	LCD_Displaystring("+:open the door");
	LCD_MoveCursor(1,0);
	LCD_Displaystring("-:change pass");

}
/*
void dislay_error(void)
{
	while(UART_Receive_Byte()!=1)
	{
		reenter_pass();
		counters++;
		_delay_ms(500);
		while(i<6)
		{
			key=KEYPAD_getPressedKeys();
			_delay_ms(500);
			if (key != '=') // Check if the user pressed '='
			{
				thpass[i] = key;
				LCD_IntegerToString(key);
				i++;
			}
			else
			{
				// The user pressed '=', break the loop and wait for confirmation.
				break;
			}
			i=0;
			thpass[5]='#';
			//UART_Send_Byte(MC1_READY);//DEACTIVATE POLLING
		}
		if(counters==2)
		{
			LCD_ClearScreen();
			LCD_Displaystring("error");
			UART_Send_Byte(1);
			while(UART_Receive_Byte()!=1){}

		}

		UART_Send_String(thpass);//SENDING ARR3

	}
}
void display_firstpass(void)
{
	while(i<6)
	{
		key=KEYPAD_getPressedKeys();
		_delay_ms(500);
		if (key != '=') // Check if the user pressed '='
		{
			fpass[i] = key;
			LCD_IntegerToString(key);
			i++;
		}
		else
		{
			// The user pressed '=', break the loop and wait for confirmation.
			break;
		}
	}
}
void display_2ndpass(void)
{
	while(i<6)
	{
		key=KEYPAD_getPressedKeys();
		_delay_ms(500);
		if (key != '=') // Check if the user pressed '='
		{
			spass[i] = key;
			LCD_IntegerToString(key);
			i++;
		}
		else
		{
			// The user pressed '=', break the loop and wait for confirmation.
			break;
		}

	}
}
*/

