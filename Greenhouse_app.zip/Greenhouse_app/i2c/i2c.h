/*
 * i2c.h
 *
 *  Created on: 14/04/2017
 *      Author: evandro
 */

#ifndef SOURCES_I2C_H_
#define SOURCES_I2C_H_

#include <stdio.h>
#include <stdlib.h>
#include <MKL25Z4.H>
#include <stdbool.h>

#define ALT0		0
#define ALT1		1
#define ALT2		2
#define ALT3		3
#define MULT0		0
#define MULT1		1
#define MULT2		2
#define I2C_WRITE	0	// Master write
#define I2C_READ	1	// Master read

bool i2c_Init(I2C_MemMapPtr i2c, uint8_t alt, uint8_t mult, uint8_t icr);
void i2c_DisableAck(I2C_MemMapPtr i2c);
void i2c_EnableAck(I2C_MemMapPtr i2c);
void i2c_RepeatedStart(I2C_MemMapPtr i2c);
void i2c_EnterRxMode(I2C_MemMapPtr i2c);
void i2c_Start(I2C_MemMapPtr i2c);
void i2c_Stop(I2C_MemMapPtr i2c);
void i2c_Wait(I2C_MemMapPtr i2c);
void i2c_WriteByte(I2C_MemMapPtr i2c,uint8_t data);
void i2c_WriteRegister(I2C_MemMapPtr i2c,uint8_t SlaveAddress,uint8_t RegisterAddress, uint8_t data);
uint8_t i2c_ReadByte(I2C_MemMapPtr i2c);
uint8_t i2c_ReadRegister(I2C_MemMapPtr i2c,uint8_t SlaveAddress,uint8_t RegisterAddress);
uint8_t i2c_ReadMultRegister(I2C_MemMapPtr i2c,uint8_t SlaveAddress,uint8_t RegisterAddress,uint8_t n_data, uint8_t *res);
void i2c_WriteMultRegister(I2C_MemMapPtr i2c,uint8_t SlaveAddress,uint8_t RegisterAddress, uint8_t n_data, uint8_t *data);
//uint8_t i2c_ReadMultRegister(I2C_MemMapPtr i2c,uint8_t SlaveAddress,uint8_t n_data, uint8_t *res);
void i2c_WriteText(I2C_MemMapPtr i2c, uint8_t SlaveAddress, uint8_t n_data, uint8_t *data);
//static void delay(uint32_t d);


#endif /* SOURCES_I2C_H_ */
