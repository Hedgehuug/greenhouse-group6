/*! ***************************************************************************
 *
 * \brief     Low level driver for the PIT
 * \file      pit.c
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
#include "pit.h"

/*!
 * \brief Initialises the Periodic Interrupt Timer (PIT)
 */
 
volatile bool timer_flag = false;
void pit_init(void)
{
			// enable the clock
		SIM->SCGC6 |= SIM_SCGC6_PIT_MASK; 
		PIT->MCR = 0x00;
		PIT_TCTRL1 = 0x02;
	PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TIE_MASK;
	PIT->CHANNEL[1].LDVAL = PIT_LDVAL_TSV(24e6);
		PIT_LDVAL1 = 2399999;
	NVIC_EnableIRQ(PIT_IRQn);
}

void PIT_IRQHandler(void)
{
    timer_flag = true;
}
