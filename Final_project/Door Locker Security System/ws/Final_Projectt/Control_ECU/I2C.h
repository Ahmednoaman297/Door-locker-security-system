/*
 * I2C.h
 *
 *  Created on: Nov 1, 2023
 *      Author: Ahmedmohamed
 */

#ifndef I2C_H_
#define I2C_H_
#include"gpio.h"
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

//typedef enum{
	//b48=4800,b96=b48*2,b144=b96*2,b57=57600,b1152=b57*2
//}I2C_BaudRate;
typedef struct{
 uint32 address;
 uint32 bit_rate;
}I2C_ConfigType;
void TWI_init(const I2C_ConfigType * Config_Ptr);
void TWI_start(void);
void TWI_stop(void);
void TWI_writeByte(uint8 data);
uint8 TWI_readByteWithACK(void);
uint8 TWI_readByteWithNACK(void);
uint8 TWI_getStatus(void);






#endif /* I2C_H_ */
