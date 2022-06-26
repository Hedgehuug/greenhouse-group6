#include "driver.h"


static uint8_t addr_ = 0x27;
I2C_Write_Func write_func_ = NULL;
Delay_Func delay_func_ = NULL;

static void PCF8574T_sendCommand4bit(uint8_t command, bool is_control_data)
{
	uint8_t sendCommand[3];

	// Set Command (Toggle E Pin)
	sendCommand[0] = (command & 0x0F) << 4;
	sendCommand[1] = sendCommand[0] | 0b00000100;
	sendCommand[2] = sendCommand[0];

	// Set RS Pin
	if (!is_control_data)
	{
		sendCommand[0] |= 0b1;
		sendCommand[1] |= 0b1;
		sendCommand[2] |= 0b1;
	}

	// Set Backlight On
	sendCommand[0] |= 0b1000;
	sendCommand[1] |= 0b1000;
	sendCommand[2] |= 0b1000;

	(*write_func_)(addr_, sendCommand, 3);
	(*delay_func_)(1);
}

// ----------------------------------------------
// Public Function
// ----------------------------------------------

void PCF8574T_Init(uint8_t i2c_addr, Delay_Func delay_func, I2C_Write_Func i2c_func)
{
	// set param
	addr_ = i2c_addr;
	delay_func_ = delay_func;
	write_func_ = i2c_func;

	// init display
	(*delay_func_)(15);
	PCF8574T_sendCommand4bit(0b0011, true); // set 8bit mode
	(*delay_func_)(5);
	PCF8574T_sendCommand4bit(0b0011, true);
	PCF8574T_sendCommand4bit(0b0011, true);
	PCF8574T_sendCommand4bit(0b0010, true);		// set 4bit mode
	PCF8574T_sendCommand8bit(0b00101000, true); // set 2line mode
	PCF8574T_sendCommand8bit(0b00001100, true); // display On, cursor Off
	PCF8574T_sendCommand8bit(0b00000001, true); // display clear
	(*delay_func_)(2);
	PCF8574T_sendCommand8bit(0b00000110, true); // set entry mode
	PCF8574T_sendCommand8bit(0b00000010, true); // move cursor to Home
}

void PCF8574T_displayString(char *string, uint8_t line)
{
	if (line == 1)
	{
		PCF8574T_sendCommand8bit(0b10000000, true); // line 1
	}
	else
	{
		PCF8574T_sendCommand8bit(0b11000000, true); // line 2
	}

	uint8_t i = 0;
	while (string[i] != '\0')
	{
		PCF8574T_sendCommand8bit(string[i], false);
		++i;
	}
}

void PCF8574T_sendCommand8bit(uint8_t command, bool is_control_data)
{
	uint8_t upperData = (command & 0xF0) >> 4;
	uint8_t lowerData = command & 0x0F;
	PCF8574T_sendCommand4bit(upperData, is_control_data);
	PCF8574T_sendCommand4bit(lowerData, is_control_data);
}
