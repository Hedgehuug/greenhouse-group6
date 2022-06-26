//timer file
#include "TPM0.h"

#include <MKL25Z4.h>



void timer0init(void){
	//SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
  SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	
	TPM1->SC |=  TPM_SC_PS(100);
	
  TPM1->MOD = 0xFFFF;
		
  TPM1->CNT = 0x00;	
	
	//TPM0->CONF = TPM_CONF_DBGMODE(1);
}

void timerStart(void){
	
	TPM1->CNT = 0x00; // reset timer 
	
	TPM1->SC |= TPM_SC_CMOD(01); // enable timer
	 
	//TPM0->SC |= TPM_SC_TOIE(1);
	
	//TPM0->SC |= TPM_SC_PS(100);
	
}

unsigned int	timerStop(void){
  		
	//TPM0->SC &= ~TPM_SC_TOIE(1);
	
	TPM1->SC &= ~TPM_SC_CMOD_MASK;
	
	//TPM0->CNT = 0x00;
	
  //temp = Micro_counter;
	
	return TPM1->CNT;
}