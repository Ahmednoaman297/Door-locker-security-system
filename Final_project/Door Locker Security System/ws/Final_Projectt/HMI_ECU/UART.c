/*
 * UART.c
 *
 *  Created on: Oct 27, 2023
 *      Author: Ahmedmohamed
 */
#include<avr/io.h>
#include"common_macros.h"
#include"UART.h"
void UART_init(const UART_ConfigType * Config_Ptr)
{
	uint16 ubrr_value=0;
	UCSRA=(1<<U2X);//DOUBLE TRANSMITION SPEED
	UCSRB=(1<<TXEN)|(1<<RXEN);//TRANSMITTER ,RECIEVER ENABLED
	UCSRC = (1<<URSEL) ;
	//LOW HAKTEB FEHA 7AGA //LOW 5LETO B ZERO H5AZEN FEL UBRRH


	//UBRRH=0;//DEH B ZERO 3SHAN H5AZEN FEL URSEL
	UCSRC=(UCSRC&0xF9)|((Config_Ptr->bit_data)<<1);

	UCSRC=(UCSRC&0xCF)|((Config_Ptr->parity)<<4);
	//UCSRC=(UCSRC&0xF7)|((Config_Ptr->stop_bit)<<4);
	UCSRC=(UCSRC&0xF7)|((Config_Ptr->stop_bit)<<4);
	ubrr_value = (uint16)(((F_CPU / (Config_Ptr->baud_rate * 8UL))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;

}
uint8 UART_Receive_Byte(void)
{
	while(BIT_IS_CLEAR(UCSRA,RXC));
	return UDR;//clear rxc ,read data f bysafar el flag 3shan hwa read only
}
void UART_Send_Byte(uint8 data)
{
	while(BIT_IS_CLEAR(UCSRA,UDRE));//1 when its empty
	UDR=data;
}
void UART_Send_String(uint8 *str)
{
	while(*str!='\0')
	{
		UART_Send_Byte(*str);
		str++;
	}
}
void UART_Receive_String(uint8 *str)
{
	uint8 i=0;
	str[i]=UART_Receive_Byte();
	while(str[i]!='#')//my own NULL
	{
		i++;
		str[i]=UART_Receive_Byte();
	}
	str[i]='\0';
}
