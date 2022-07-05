//sensor
#include "sensor.h"


void ADCinit(void){
	
	SIM->SCGC6 |= SOIL_MASK(SIM_SCGC6_ADC0_SHIFT);
	
	SIM->SCGC5 |= SIM_SCGC5_PORTB(1);
	
	PORTB->PCR[0] &= ~0x7FF;
	
	ADC0->CFG1 = 0x9C;
	
	ADC0->SC2 = 0;

}

uint16_t checkAnalog(int channel)
{
	ADC0->SC1[0] = channel;
	
	while (! (ADC0->SC1[0] & ADC_SC1_COCO_MASK))
	{;}
		
	uint16_t res = ADC0->R[0];
	return res;
}

int soil_Conv(void)
{
volatile uint16_t adc_value0;
int perc0;	
float scale;
int offset;
		
		adc_value0 = 0xFFFF - checkAnalog(8);;
		scale = (WATER_VALUE - AIR_VALUE);
		offset = -AIR_VALUE*(100-0)/(WATER_VALUE - AIR_VALUE) + 0;
			
		if(adc_value0 >= WATER_VALUE)
		{
			perc0 = 100;
		} else if(adc_value0 <= AIR_VALUE)
		{
			perc0 = 0;
		} else
		{
			perc0 = adc_value0*(100/scale) + offset;
		}
		
			return perc0;
}
