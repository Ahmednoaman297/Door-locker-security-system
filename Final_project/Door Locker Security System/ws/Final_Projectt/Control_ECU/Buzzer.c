/*
 * Buzzer.c
 *
 *  Created on: Nov 2, 2023
 *      Author: Ahmedmohamed
 */
#include"Buzzer.h"
#include "timer1.h"
void Buzzer_init()
{
	GPIO_setupPinDirection(buzzer_PORT_ID,buzzer_PIN_ID,PIN_OUTPUT);
	GPIO_writePin( buzzer_PORT_ID, buzzer_PIN_ID , LOGIC_LOW);

}
void Buzzer_on(void)
{
	GPIO_writePin( buzzer_PORT_ID, buzzer_PIN_ID , LOGIC_HIGH);

}
void Buzzer_off(void)
{
	GPIO_writePin( buzzer_PORT_ID, buzzer_PIN_ID , LOGIC_LOW);

}
