/*
 * EEPROM.h
 *
 *  Created on: Nov 1, 2023
 *      Author: Ahmedmohamed
 */

#ifndef EEPROM_H_
#define EEPROM_H_
#include"gpio.h"

#define ERROR 0
#define SUCCESS 1

uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data);




#endif /* EEPROM_H_ */
