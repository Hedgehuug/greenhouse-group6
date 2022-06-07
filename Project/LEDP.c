#include <stdio.h>
#include <stdbool.h>
#include "LEDP.h"

extern uint16_t color; // this is how strong the light will be 

void tpm2_init(void)
{ 
	SIM->SCGC5 |= SIM_SCGC5_PORTE(1);   //activate timer for port e 21,22;
	
	SIM->SCGC6 |= SIM_SCGC6_TPM1(1); // activate TPM2:CH0,CH1
	
	PORTE->PCR[20] = PORT_PCR_MUX(4); //on mux
	//PORTE->PCR[22] = PORT_PCR_MUX(3); //on mux
	
	TPM1->MOD = 0xFFFF;
	
	TPM1->CONTROLS[0].CnSC = TPM_CnSC_MSB(1) | TPM_CnSC_ELSA(1); // for ch0
  //TPM2->CONTROLS[1].CnSC = TPM_CnSC_MSB(1) | TPM_CnSC_ELSA(1); // for ch1
	
	TPM1->SC = TPM_SC_CMOD(1); //turn on
}


inline void color_pwmcontrol(const uint16_t color)
{
    // Set the channel compare values
    TPM1->CONTROLS[0].CnV = color;

    TPM1->CNT = 0;
}


inline void color_onoff(const bool c) // this tuns off and on the light by changing color to 0
{
    // Set convenient on values for each color here from 0 to 65535   
    color = 2*1024;

    // Set the channel compare values
    TPM1->CONTROLS[0].CnV = c ? color : 65535;

    TPM1->CNT = 0;
}


