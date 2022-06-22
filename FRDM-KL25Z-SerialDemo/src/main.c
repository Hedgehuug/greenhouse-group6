/******************************************************************************
 * Project    : MIC2-V Serial demo
 * Copyright  : 2021 HAN University of Applied Sciences
 * Author     : Hugo Arends
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 ******************************************************************************
 */
#include <MKL25Z4.H>
#include <stdio.h>
#include <math.h>
#include "rgb.h"
#include "timers.h"
#include "uart0.h"

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void)
{
    rgb_init();
    uart0_init();
    pit_init(BUS_CLOCK_FREQUENCY/TICK_FREQUENCY);

    rgb_on(false, false, false);

    uint32_t fake_sensor=0;
    
    pit_start();

    while (1)
    {
        // Sensor update?
        if(fake_sensor_update_flag == 1)
        {
            // Reset the flag
            fake_sensor_update_flag = 0;
            
            // Get (fake) sensor value
            fake_sensor = (fake_sensor+1) % 1000;
            
            // Create a 3 digit ASCII string from the sensor value and terminate
            // it with a \n character
            char str[32];
            sprintf((char *)str, "%03d\n", fake_sensor);
            uart0_send_string(str);
        }

        // Enough data available?
        if(q_size(&RxQ) >= 4)
        {
            uint8_t r;
            uint8_t g;
            uint8_t b;

            q_dequeue(&RxQ, &r);
            q_dequeue(&RxQ, &g);
            q_dequeue(&RxQ, &b);
            
            // Translate each received character from ASCII to integer
            r = r - '0';
            g = g - '0';
            b = b - '0';
            
            uint8_t c;
            
            // Get the fourth and final character
            q_dequeue(&RxQ, &c);
            
            // Is the fourth received character a \n?
            if(c == '\n')
            {
                // Use the first three received characters to control the LEDs
                rgb_on(r,g,b);
            }
            else
            {
                // Unexpected data in the queue!
                // Empty the queue
                while(!q_empty(&RxQ))
                {
                    q_dequeue(&RxQ, &c);
                }
            }
        }
    }
}
