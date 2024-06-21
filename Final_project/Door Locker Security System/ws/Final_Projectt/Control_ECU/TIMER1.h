/*
 * TIMER1.h
 *
 *  Created on: Nov 2, 2023
 *      Author: Ahmedmohamed
 */

#ifndef TIMER1_H_
#define TIMER1_H_
#include"gpio.h"
/*typedef enum{
	normal,toggle,inverting,non_inverting
};*/
typedef enum{
	pre1,pre8,pre64,pre128,pre256,pre1024,falling_edge,rising_edge
}Timer1_Prescaler;
typedef enum{
	Normal,ctc=4,FAST_PWM=14,FAST_PWM2=15
}Timer1_Mode;
typedef struct {
	uint16 initial_value;
	uint16 compare_value; // it will be used in compare mode only.
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
} Timer1_ConfigType;
typedef struct
{
	Timer1_Mode mode;
}mode_confg;
void Timer1_init(const Timer1_ConfigType * Config_Ptr);
void Timer1_deInit(void);
void Timer1_AsetCallBack(void(*a_ptr)(void));
void TIMER1_startCount(Timer1_Prescaler prescaler);
void TIMER1_stopCount(void);



#endif /* TIMER1_H_ */
