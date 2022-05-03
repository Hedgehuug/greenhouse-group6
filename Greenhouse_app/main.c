
#include <stdio.h>
#include <MKL25Z4.H>

void init_DAC()
{
	SIM->SCGC5 = SIM_SCGC5_PORTB_MASK;
	SIM->SCGC6 |= (1UL << SIM_SCGC6_ADC0_SHIFT);
	
	ADC0->CFG1 = 0x9C;
}

int main(void)
{
	volatile unsigned res = 0;
	while (1){
		ADC0->SC1[0] = 0x03;
		
		while (! (ADC0->SC1[0] & ADC_SC1_COCO_MASK))
		{;}
			
		res = ADC0->R[0];
		}
	return 0;
}