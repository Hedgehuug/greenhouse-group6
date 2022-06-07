//sensor
#include "sensor.h"


void ADCinit(void){
	
	SIM->SCGC6 |= MASK(SIM_SCGC6_ADC0_SHIFT);
	
	SIM->SCGC5 |= SIM_SCGC5_PORTB(1);
	
	PORTB->PCR[0] &= ~0x7FF;
	
	ADC0->CFG1 = 0x9C;
	
	ADC0->SC2 = 0;

}
