/*
 * PCF8574T_LCD_Driver.h
 *
 *  Created on: May 13, 2020
 *      Author: user1
 */

#ifndef INC_PCF8574T_LCD_DRIVER_H_
#define INC_PCF8574T_LCD_DRIVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <MKL25Z4.H>
#include <stdbool.h>

// I2c Write Function
typedef void (*I2C_Write_Func)(uint8_t addr, uint8_t *send_data, uint8_t send_data_len);

// Delay Function
typedef void (*Delay_Func)(uint16_t delay_time_ms);

// Public Function
void PCF8574T_Init(uint8_t i2c_addr, Delay_Func delay_func, I2C_Write_Func i2c_func);
void PCF8574T_displayString(char *string, uint8_t line);
void PCF8574T_sendCommand8bit(uint8_t command, bool is_control_data);

#endif /* INC_PCF8574T_LCD_DRIVER_H_ */
