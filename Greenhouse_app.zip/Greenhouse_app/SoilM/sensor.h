#ifndef SENSOR_H
#define SENSOR_H

#define SOIL_MASK(x)   (1UL<<(x))

#include "MKL25Z4.h" // Device header

#define WATER_VALUE (47000)
#define AIR_VALUE (535)

extern volatile uint16_t result;
extern volatile uint16_t res;

void ADCinit(void);

uint16_t checkAnalog(int channel);

int soil_Conv(void);

#endif//end h file
