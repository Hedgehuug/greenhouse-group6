#include <stdio.h>
#include <stdbool.h>
#include "LEDP.h"

extern uint16_t color; //  PTE22
extern uint16_t heat;  //  PTA2
extern uint16_t fan;   // PTA4

void tpm_init(void)
{ 
	SIM->SCGC5 |= SIM_SCGC5_PORTE(1) | SIM_SCGC5_PORTA(1);   
	SIM->SCGC6 |= SIM_SCGC6_TPM2(1) | SIM_SCGC6_TPM0(1);; 
	
	PORTE->PCR[22] |= PORT_PCR_MUX(3) ; 	
	PORTA->PCR[2] |= PORT_PCR_MUX(3);
	PORTA->PCR[4] |= PORT_PCR_MUX(3);
	
	PORTE->PCR[22] |= PORT_PCR_PE(1);
	PORTE->PCR[22] |= PORT_PCR_PS(0);
	
	PORTA->PCR[4] |= PORT_PCR_PE(1);
	PORTA->PCR[4] |= PORT_PCR_PS(0);

	PORTA->PCR[2] |= PORT_PCR_PE(1);
	PORTA->PCR[2] |= PORT_PCR_PS(0);



	TPM2->MOD = 0xFFFF;
	TPM2->CONTROLS[0].CnSC |= TPM_CnSC_MSB(1) | TPM_CnSC_ELSA(1); // for ch0
  TPM2->CONTROLS[1].CnSC |= TPM_CnSC_MSB(1) | TPM_CnSC_ELSA(1); // for ch1	
	TPM2->SC = TPM_SC_CMOD(1); //turn on
	     
	TPM0->MOD = 0xFFFF;
	TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB(1) | TPM_CnSC_ELSA(1); // for ch1
	TPM0->SC = TPM_SC_CMOD(1); //turn on
}

//lights
inline void color_pwmcontrol(const uint16_t color)
{
    // Set the channel compare values
    TPM2->CONTROLS[0].CnV = color;
}

inline void color_onoff(const bool c) // this tuns off and on the light by changing color to 0
{
    // Set the channel compare values
    TPM2->CONTROLS[0].CnV = c ? color : 10000;
}

//water
inline void heat_pwmcontrol(const uint16_t heat)
{
    // Set the channel compare values
    
	  TPM2->CONTROLS[1].CnV = heat;
}

inline void heat_onoff(const bool h) // this tuns off and on 
{
    // Set the channel compare values
   	TPM2->CONTROLS[1].CnV = h ? heat : 30000;
}

//fan
inline void fan_pwmcontrol(const uint16_t fan)
{
    // Set the channel compare values
    TPM0->CONTROLS[1].CnV = fan;
}


inline void fan_onoff(const bool f) // this tuns off and on 
{
    // Set the channel compare values
    TPM0->CONTROLS[1].CnV = f ? fan : 30000;
}
