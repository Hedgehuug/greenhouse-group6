#include <MKL25Z4.H>
#include <stdio.h>

#include "LEDP.h"

uint16_t color = 1024;
uint16_t water = 1024;
uint16_t fan = 1024;

int main(void)
{
	tpm_init();
	
  color_onoff(true);
	
	water_onoff(true);
	
	fan_onoff(true);
	
  return 0;
}