/*
 * LCD.c
 *
 *  Created on: Oct 3, 2023
 *      Author: Ahmedmohamed
 */
#include <util/delay.h>
#include "LCD.h"
void LCD_SendCommand(uint8 command)
{
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);//RS=0
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);//E=1
	_delay_ms(1);
	GPIO_writePort(LCD_DATA_PORT_ID,command); /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);//E=1
	_delay_ms(1);

}

void LCD_DisplayCharacter(uint8 command)
{

	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);//RS=0
		_delay_ms(1);
		GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);//E=1
		_delay_ms(1);
		GPIO_writePort(LCD_DATA_PORT_ID,command); /* out the required command to the data bus D0 --> D7 */
		_delay_ms(1);
		GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);//E=1
		_delay_ms(1);


}
void LCD_Displaystring(char *string)
{

	while(*string!='\0')
	{
		LCD_DisplayCharacter(*string);
		string++;
	}


}

void LCD_MoveCursor(uint8 row, uint8 col)
{
	uint8 cursor;
	switch(row)
	{
	case 0:
		cursor=col;
		break;
	case 1:
			cursor=col+0x40;
			break;
		case 2:
			cursor=col+0x10;
				break;
		case 3:
			cursor=col+0x50;
				break;
	}
	LCD_SendCommand(cursor|LCD_SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(uint8 row, uint8 col,char *string)
{
	LCD_MoveCursor(row,col);
	LCD_Displaystring(string);
}


void LCD_IntegerToString(uint8 data)
{
	char buffer[16];
	itoa(data,buffer,10);
	LCD_Displaystring(buffer);
}

void LCD_INIT(void)
{
	GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT); /* PD4 Output Pin */
	GPIO_setupPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT); /* PD5 Output Pin */
	GPIO_setupPortDirection(LCD_DATA_PORT_ID,PORT_OUTPUT); /* All PORTC pins are o/p pins */
	LCD_SendCommand(0x38);//2LINES AND 5x8 MATRIX
	LCD_SendCommand(0x0C);//DISPLAY ON ,CURSOR OFF
	LCD_SendCommand(0x01);//CLEAR DISPLAY

}
void LCD_ClearScreen()
{
	LCD_SendCommand(LCD_CLEAR_COMMAND);
}

