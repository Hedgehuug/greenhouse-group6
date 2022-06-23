#include <MKL25Z4.H>
#include <stdio.h>

#include "LEDP.h"

uint16_t color = 32700;
uint16_t heat = 32700;
uint16_t fan = 32700;

int main(void)
{
	tpm_init();
	
	color_onoff(false);
	
	heat_onoff(false);
	
	fan_onoff(false);
	
	while(1)
	{;}
  return 0;
}