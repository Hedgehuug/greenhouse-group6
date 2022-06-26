//DHT22 Header-File
#ifndef DHT11_H
#define DHT11_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "MKL25Z4.h"                    // Device header

#include "../tpm1/TPM0.h"

#include "../uart1/uart1.h"

#define DHTLIB_OK				0
#define DHTLIB_ERROR_CHECKSUM	-1
#define DHTLIB_ERROR_TIMEOUT	-2

#define MASK(x)   (1UL << (x))

#define LOW    0  //(!(PTA->PDIR & MASK(1)))
#define HIGH   1  //(PTA->PDIR & MASK(1))



typedef struct DHT{
	uint8_t humidity;
	uint8_t temperature;
} DHT_type;

int getDataBit(void);
DHT_type dht_function();

void checkResponse(unsigned int waitTimeUS, unsigned int margin, bool pinValue);


#endif //DHT22_H
