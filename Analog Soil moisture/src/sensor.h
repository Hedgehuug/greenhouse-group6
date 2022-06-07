#ifndef SENSOR_H
#define SENSOR_H

#define MASK(x)   (1UL<<(x))

#include "MKL25Z4.h" // Device header

extern volatile uint16_t result;
extern volatile uint16_t res;

void ADCinit(void);

#endif//end h file
