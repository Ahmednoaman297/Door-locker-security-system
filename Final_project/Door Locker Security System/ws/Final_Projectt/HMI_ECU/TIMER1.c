/*
 * TIMER1.c
 *
 *  Created on: Nov 2, 2023
 *      Author: Ahmedmohamed
 */
#include"avr/io.h"
#include"TIMER1.h"
#include<avr/interrupt.h>
static volatile void (*B_callBackPtr)(void) = NULL_PTR;
static volatile void (*A_callBackPtr)(void) = NULL_PTR;
static volatile void (*g_callBackPtrOvf)(void) = NULL_PTR;


ISR(TIMER1_COMPA_vect)
{
	if(A_callBackPtr != NULL_PTR)
	{
		(*A_callBackPtr)();
	}
}
ISR(TIMER1_COMPB_vect)
{
	if(B_callBackPtr != NULL_PTR)
	{
		(*B_callBackPtr)();
	}
}
ISR(TIMER1_OVF_vect)
{
	if(B_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtrOvf)();
	}
}
void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	uint8 MODE=Config_Ptr->mode;
		TCNT1=(Config_Ptr->initial_value);
		TCCR1A|=(1<<FOC1A);
		//TCCR1A=(1<<Config_Ptr->mode);
		//TCCR1B=(TCCR1B&0xE7)|((1<<Config_Ptr->mode)<<3);
	//	TCCR1B=(TCCR1B & 0xF8)|(Config_Ptr->prescaler);
		TCCR1B = (Config_Ptr->prescaler) | ((Config_Ptr->mode<<1)&0x08);

	if(MODE==Normal)
		{
			TIMSK |= (1<<TOIE1);
		}

	else if(MODE==ctc)
		{

			OCR1A=(Config_Ptr->compare_value);
			TIMSK |= (1<<OCIE1A);
			//TCCR1B|=(((Config_Ptr->mode)&(~0x03))<<1);
			//TCCR1B=(TCCR1B & 0xF7) | ((Config_Ptr->mode)<<2);
		}
	/*#elif(MODE==FAST_PWM)
		{
			TCCR1B=(1<<WGM12)|(1<<WGM13)|(1<<WGM11);

			DDRD|=(1<<5);
			ICR1=((8000000)/N)-1;
			if(FAST_PWM_mode==inverting)
			{
				TCCR1A=((1<<inverting)<<6);
			}
			else if(FAST_PWM_mode==non_inverting)
			{
				TCCR1A=((1<<non_inverting)<<6);
			}


		}*/
}
void Timer1_deInit(void)
{
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;
	A_callBackPtr = NULL_PTR;
	B_callBackPtr = NULL_PTR;

}
void Timer1_AsetCallBack(void(*a_ptr)(void))
{
	A_callBackPtr = a_ptr;

}
void TIMER1_startCount(Timer1_Prescaler prescaler)
{
	TCCR1B |= (1<<WGM12);
	TCCR1B=(TCCR1B & 0xF8)|(prescaler);

}

void TIMER1_stopCount(void)
{
	TCCR1B =0;
}

