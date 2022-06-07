#include <MKL25Z4.H>
#include <stdio.h>

#include "LEDP.h"

uint16_t color = 2*1024;

int main(void)
{
	tpm2_init();

	
	while(1)    //simple code to check if it's working, i suggest making an interupt that checks c status of true and false to turn on and off
	{           //and another interrupt that will either dim the light or power it with ldr

		color_onoff(false);
z	}
  return 0;
}