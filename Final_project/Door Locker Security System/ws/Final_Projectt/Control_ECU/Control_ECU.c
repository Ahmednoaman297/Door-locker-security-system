#include <avr/io.h>
#include "DC_motor.h"
#include "UART.h"
#include <util/delay.h>
#include "EEPROM.h"
#include "I2C.h"
#include "TIMER1.h"
#include "Buzzer.h"

#define MC1_READY 0x10
#define success 1
#define failed 0

uint16 ticks = 0;
uint8 flag = 1;
uint8 arr1[7]; // First pass
uint8 arr2[7]; // Second pass
uint8 arr3[7]; // Confirmation of opening door
uint8 tick = 0;
uint8 counter = 0;
uint8 temp=0;
uint8 operation=0;


void motor(void) {
	ticks++;

		DcMotor_Rotate(CW,100);

	 if(ticks==15)
	{
		//UART_Send_Byte(success);
		DcMotor_Rotate(STOP,0);
	}
	else if(ticks==18)
	{
		UART_Send_Byte(success);
		DcMotor_Rotate(CCW,100);

	}
	else if(ticks==30)
	{
		DcMotor_Rotate(STOP,0);
		UART_Send_Byte(success);
		ticks=0;
		TIMER1_stopCount();

	}
}

void buzzer_time(void) {
	tick++;
		Buzzer_on();
	 if (tick == 60) {
		Buzzer_off();
		UART_Send_Byte(success);
		tick=0;
		TIMER1_stopCount();

	}
}

int main() {
	SREG |= (1 << 7);
	// Timer1 enable
	Timer1_ConfigType SET = {0, 7812, pre1024, ctc};
	Timer1_init(&SET);
	// UART enable
	UART_ConfigType setup = {bit8, disabled, bit_1, b96	};
	UART_init(&setup);
	// Enable buzzer
	Buzzer_init();
	// Enable DC motor
	DcMotor_Init();
	// Enable TWI
	I2C_ConfigType SETUPP = {0b00000010, 400000};
	TWI_init(&SETUPP);
	Timer1_AsetCallBack(motor);
	TIMER1_stopCount();

	while (UART_Receive_Byte() != MC1_READY) {} // POLLING
	UART_Receive_String(arr1);
	UART_Receive_String(arr2);

	for (int i = 0; i < 7; i++) {
		if (arr1[i] != arr2[i]) {
			flag = 0;
			break;
		}
	}

	if (flag == 1) {
		for (int i = 0; i < 5; i++) {
			EEPROM_writeByte((0x0311 + i), arr1[i]);
			_delay_ms(10); // Wait for write operation to complete
		}
		UART_Send_Byte(success);


	} else {
		UART_Send_Byte(failed);
	}

	while(1)
	{
		//switch
		operation=UART_Receive_Byte();
		switch (operation)
		{
		case '+':
		{
			while (UART_Receive_Byte() != MC1_READY) {} // POLLING
			UART_Receive_String(arr3);

			for (int i = 0; i < 3; i++) {
				flag = 1;
				//counter++;
				if(i==2)
				{
					Timer1_AsetCallBack(buzzer_time);
					TIMER1_stopCount();
					TIMER1_startCount(pre1024);
					break;
				}
				for (int i = 0; i < 5; i++)
				{



					EEPROM_readByte((0x0311 + i),&temp);

					if (temp!= arr3[i])
					{
						flag = 0;
						break;
					}
				}

				if (flag == 1) {
					UART_Send_Byte(success);
					TIMER1_startCount(pre1024);

					break;
				} else {
					UART_Send_Byte(failed);
					UART_Receive_String(arr3);

				}

			}
			/*while(UART_Receive_Byte()==1)
			{
				Timer1_AsetCallBack(buzzer_time);
				TIMER1_stopCount();
				TIMER1_startCount(pre1024);
				break;
			}*/
		}
		break;
		case '-':
		{
			while (UART_Receive_Byte() != MC1_READY) {} // POLLING
			UART_Receive_String(arr3);

			for (int i = 0; i < 3; i++) {
				flag = 1;
				if(i==2)
				{
					Timer1_AsetCallBack(buzzer_time);
					TIMER1_stopCount();
					TIMER1_startCount(pre1024);
					break;
				}
				for (int i = 0; i < 5; i++)
				{



					EEPROM_readByte((0x0311 + i),&temp);

					if (temp!= arr3[i])
					{
						flag = 0;
						break;
					}
				}

				if (flag == 1) {
					UART_Send_Byte(1);
					while (UART_Receive_Byte() != MC1_READY) {} // POLLING
					UART_Receive_String(arr1);
					UART_Receive_String(arr2);

					for (int i = 0; i < 7; i++) {
						if (arr1[i] != arr2[i]) {
							flag = 0;
							break;
						}
					}

					if (flag == 1) {
						for (int i = 0; i < 5; i++) {
							EEPROM_writeByte((0x0311 + i), arr1[i]);
							_delay_ms(10); // Wait for write operation to complete
						}
						UART_Send_Byte(success);


					} else {
						UART_Send_Byte(failed);
					}
				} else {
					UART_Send_Byte(failed);
					UART_Receive_String(arr3);

				}

			}
			/*while(UART_Receive_Byte()==1)
			{
				Timer1_AsetCallBack(buzzer_time);
				TIMER1_stopCount();
				TIMER1_startCount(pre1024);
				break;
			}*/
		}
		break;

		}
	}
}
