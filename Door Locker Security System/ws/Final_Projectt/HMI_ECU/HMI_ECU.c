/*
 * keypad_main.c
 *
 *  Created on: Oct 7, 2023
 *      Author: Ahmedmohamed
 */
#include"keypad_flasha.h"
#include "LCD.h"
#include"avr/io.h"
#include"UART.h"
#include <util/delay.h> /* For the delay functions */
#include"TIMER1.h"
#include"displayer.h"
#define MC1_READY 0x10
uint8 key=0;
uint8 fpass[7]={0};
uint8 spass[7]={0};
uint8 thpass[7]={0};
uint8 flag_main=0;
uint8 i=0;
uint8 counters=0;
uint8 tick=0;
void take_password(uint8 *arr)
{
	i=0;
	key=KEYPAD_getPressedKeys();
	_delay_ms(300);
	while(key != '=')
	{
		arr[i] = key;
		LCD_DisplayCharacter('*');
		i++;
		key=KEYPAD_getPressedKeys();
		_delay_ms(300);
	}
	arr[i]='#';
	arr[i+1]='\0';

}
void block_lcd(void) {
	tick++;
	if (tick == 60) {
		LCD_ClearScreen();
		tick=0;
		TIMER1_stopCount();

	}
}
int main(void)
{
	SREG|=(1<<7);
	//timer1 enable
	LCD_INIT();
	UART_ConfigType setup={bit8 ,disabled ,bit_1 , b96};
	UART_init(&setup);

	Timer1_ConfigType SET = {0, 7812, pre1024, ctc};
	Timer1_init(&SET);

	dis_pass1();
	take_password(fpass);
	reenter_pass();
	take_password(spass);
	LCD_ClearScreen();

	UART_Send_Byte(MC1_READY);//DEACTIVATE POLLING
	UART_Send_String(fpass);
	UART_Send_String(spass);
	while(UART_Receive_Byte()!=1)
	{
		dis_pass1();
		take_password(fpass);
		reenter_pass();
		take_password(spass);
		LCD_ClearScreen();
		/*LCD_displayStringRowColumn(0,0,fpass);
				LCD_displayStringRowColumn(1,0,spass);
				_delay_ms(3000);*/
		UART_Send_Byte(MC1_READY);//DEACTIVATE POLLING
		UART_Send_String(fpass);
		//	_delay_ms(10);
		UART_Send_String(spass);
	}
	while(1)
	{
		screen_door();
		key=KEYPAD_getPressedKeys();
		UART_Send_Byte(key);
		switch(key)
		{
		case '+':
		{
			_delay_ms(100);
			UART_Send_Byte(key);
			key=0;
			dis_pass1();
			take_password(thpass);
			UART_Send_Byte(MC1_READY);//DEACTIVATE POLLING
			UART_Send_String(thpass);//SENDING ARR3
			while(UART_Receive_Byte()!=1)
			{
				reenter_pass();
				counters++;
				_delay_ms(100);
				take_password(thpass);
				if(counters==2)
				{

					LCD_ClearScreen();
					LCD_Displaystring("error");
					Timer1_AsetCallBack(block_lcd);
					UART_Send_Byte(1);
					//	flag_main=1;
					/*while(UART_Receive_Byte()!=1){}
					break;*/

				}
				UART_Send_String(thpass);//SENDING ARR3
			}
			if(counters!=2)
			{
				LCD_ClearScreen();
				LCD_Displaystring("door is opening");
				//	closing=UART_Receive_Byte();
				while(UART_Receive_Byte()!=1){}
				LCD_ClearScreen();
				LCD_Displaystring("door is closing");
				while(UART_Receive_Byte()!=1){}
			}
			counters=0;

		}
		break;
		case'-':
		{
			_delay_ms(100);
			UART_Send_Byte(key);
			key=0;
			dis_pass1();
			take_password(thpass);
			UART_Send_Byte(MC1_READY);//DEACTIVATE POLLING
			UART_Send_String(thpass);//SENDING ARR3

			while(UART_Receive_Byte()!=1)
			{

				reenter_pass();
				counters++;
				_delay_ms(100);
				take_password(thpass);
				if(counters==2)
				{
					LCD_ClearScreen();
					LCD_Displaystring("error");
					Timer1_AsetCallBack(block_lcd);
					UART_Send_Byte(1);
				}

				UART_Send_String(thpass);//SENDING ARR3

			}

			if(counters!=2)
			{
				LCD_ClearScreen();
				dis_pass1();
				take_password(fpass);
				reenter_pass();
				take_password(spass);
				LCD_ClearScreen();
				UART_Send_Byte(MC1_READY);//DEACTIVATE POLLING
				UART_Send_String(fpass);
				UART_Send_String(spass);
			}
			counters=0;

		}

		break;


		}
	}
}
