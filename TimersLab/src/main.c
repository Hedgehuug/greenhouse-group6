/*! ***************************************************************************
 *
 * \brief     SerialLab project
 * \file      main.c
 * \author    Hugo Arends
 * \date      July 2021
 *
 * \copyright 2021 HAN University of Applied Sciences. All Rights Reserved.
 *            \n\n
 *            Permission is hereby granted, free of charge, to any person
 *            obtaining a copy of this software and associated documentation
 *            files (the "Software"), to deal in the Software without
 *            restriction, including without limitation the rights to use,
 *            copy, modify, merge, publish, distribute, sublicense, and/or sell
 *            copies of the Software, and to permit persons to whom the
 *            Software is furnished to do so, subject to the following
 *            conditions:
 *            \n\n
 *            The above copyright notice and this permission notice shall be
 *            included in all copies or substantial portions of the Software.
 *            \n\n
 *            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *            OTHER DEALINGS IN THE SOFTWARE.
 *
 *****************************************************************************/
#include <MKL25Z4.H>
#include <stdio.h>

#include "pit.h"
#include "rgb.h"
#include "tpm1.h"
#include "uart0.h"

// Local function prototypes
static void delay_us(uint32_t d);
uint32_t counter = 0;
volatile unsigned res = 0;


/*!
 * \brief Main application
 */
 
 
 void init_DAC()
{
	SIM->SCGC5 = SIM_SCGC5_PORTB_MASK;
	SIM->SCGC6 |= (1UL << SIM_SCGC6_ADC0_SHIFT);
	
	ADC0->CFG1 = 0x9C;
}

int main(void)
{
	/*
    rgb_init();
    pit_init();
    tpm1_init();
    uart0_init();
    
    uart0_send_string("Timers Lab\r\n");
    while(1)
    {
			if (timer_flag == true)
				{
					if( counter >= 9)
					{
						counter = 0;
						rgb_onoff(1,1,1);
					}
					else
					{
						rgb_onoff(0,0,0);
						counter++;
					}
					timer_flag = false;
				}
				
				
    }
		*/

	init_DAC();
	while (1){
		ADC0->SC1[0] = 0x03;
		
		while (! (ADC0->SC1[0] & ADC_SC1_COCO_MASK))
		{;}
			
		res = ADC0->R[0];
		}
	return 0;

}

/*!
 * \brief Creates a blocking delay
 *
 * Software delay of approximately 1 us, depending on CPU clock frequency
 * and optimization level
 * - CPU clock: 48 MHz
 * - Optimization level: -O3
 * - Optimize for time: disabled
 *
 * \param[in]  d  delay in microseconds
 */
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
