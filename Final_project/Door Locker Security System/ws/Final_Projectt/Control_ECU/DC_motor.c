/*
 * DC_motor.c
 *
 *  Created on: Oct 14, 2023
 *      Author: Ahmedmohamed
 */

#include"gpio.h"
#include"DC_motor.h"
#include"TIMER0.h"
void DcMotor_Init(void)
{
	GPIO_setupPinDirection(IN1_PORT_ID,IN1_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(IN2_PORT_ID,IN2_PIN_ID,PIN_OUTPUT);


}
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	if(state==CW)
	{
		GPIO_writePin(IN1_PORT_ID,IN1_PIN_ID,LOGIC_LOW);
		GPIO_writePin(IN2_PORT_ID,IN2_PIN_ID,LOGIC_HIGH);
	}
	else if(state==CCW)
		{
			GPIO_writePin(IN1_PORT_ID,IN1_PIN_ID,LOGIC_HIGH);
			GPIO_writePin(IN2_PORT_ID,IN2_PIN_ID,LOGIC_LOW);
		}
	else if(state==STOP)
		{
			GPIO_writePin(IN1_PORT_ID,IN1_PIN_ID,LOGIC_LOW);
			GPIO_writePin(IN2_PORT_ID,IN2_PIN_ID,LOGIC_LOW);
		}
	PWM_Timer0_Init(speed*(250/100));



}
