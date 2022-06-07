
#include <stdio.h>
#include <stdlib.h>
#include <MKL25Z4.H>
#include <stdbool.h>

void init_DAC()
{
	SIM->SCGC5 = SIM_SCGC5_PORTB_MASK; //Enable clock for PORTB
	SIM->SCGC6 |= (1UL << SIM_SCGC6_ADC0_SHIFT);
	
	ADC0->CFG1 = 0x9C;
}

// Move to header file
// Gets updated by the sensors, used to trigger activation functions
volatile bool trigger_flags[8] = {0,0,0,0,0,0,0,0};
// Shows current status of actuators, used for cross-reference with trigger_flags
volatile bool status_flags[8] = {0,0,0,0,0,0,0,0};
// To-do:
// Get header file reference because uVision doesn't set it up for us

int main(void)
{
		init_DAC();
	PORTB->PCR[0] = PORT_PCR_MUX(1);
	PORTB->PCR[1] = PORT_PCR_MUX(1);
	// Result of the check
	volatile unsigned res = 0;
	while (1){
		ADC0->SC1[0] = 0x03;
		
		while (! (ADC0->SC1[0] & ADC_SC1_COCO_MASK))
		{;}
			
		res = ADC0->R[0];
		if (res > 50000){
		PTB->PDDR &= ~(1<<0);
		}
		else
		{
			PTB->PDDR |= (1<<0);
		}
		
		
		if (res > 35000){
		PTB->PDDR &= ~(1<<1);
		}
		else
		{
			PTB->PDDR |= (1<<1);
		}
			
			
			
		}
	return 0;
}