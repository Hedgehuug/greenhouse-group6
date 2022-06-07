//MAIN
#include "MKL25Z4.h"                    // Device header
#include <stdio.h> 
#include "sensor.h"

static void delay_us(uint32_t d);

volatile uint16_t res;
volatile uint16_t result;

int main(void){
	
  ADCinit();
	
	while(1){
		//delay_us(100000);
		
		ADC0->SC1[0] = 0x08;
		
		while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK))
		{}
			
		result = ADC0->R[0];
			
		res = 0xFFFF - result;
		}
	}

static void delay_us(uint32_t d)
{

#if (CLOCK_SETUP != 1)
#warning This delay function does not work as designed
#endif

    volatile uint32_t t;

    for(t=4*d; t>0; t--)
    {
        __asm("nop");
        __asm("nop");
    }
}
