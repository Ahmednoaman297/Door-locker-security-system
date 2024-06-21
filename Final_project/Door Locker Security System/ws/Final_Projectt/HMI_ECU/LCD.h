/*
 * LCD.h
 *
 *  Created on: Oct 3, 2023
 *      Author: Ahmedmohamed
 */

#ifndef LCD_H_
#define LCD_H_
#include "gpio.h"
#define LCD_DATA_PORT_ID   PORTA_ID

#define LCD_RS_PORT_ID     PORTC_ID

#define LCD_RS_PIN_ID      PIN2_ID

#define LCD_E_PORT_ID      PORTC_ID

#define LCD_E_PIN_ID       PIN0_ID

#define LCD_CLEAR_COMMAND              0x01
#define LCD_GO_TO_HOME                 0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE  0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE   0x28
#define LCD_CURSOR_OFF                 0x0C
#define LCD_CURSOR_ON                  0x0E
#define LCD_SET_CURSOR_LOCATION        0x80


void LCD_SendCommand(uint8 command);
void LCD_DisplayCharacter(uint8 command);
void LCD_Displaystring(char *string);
void LCD_MoveCursor(uint8 row, uint8 col);
void LCD_displayStringRowColumn(uint8 row, uint8 col,char *string);
void LCD_ClearScreen();
void LCD_IntegerToString(uint8 data);

void LCD_INIT(void);




#endif /* LCD_H_ */
