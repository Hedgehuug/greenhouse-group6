#include <stdio.h>
#include <stdbool.h>
#include "lights.h"

extern uint16_t color; // this is how strong the light will be 
extern uint16_t water;
extern uint16_t fan;

void tpm_init(void)
{ 
	SIM->SCGC5 |= SIM_SCGC5_PORTE(1);   
	SIM->SCGC6 |= SIM_SCGC6_TPM2(1); 
	PORTE->PCR[22] |= PORT_PCR_MUX(3) | PORT_PCR_PE(1) | PORT_PCR_PS(0); 
	PORTE->PCR[23] |= PORT_PCR_MUX(3) | PORT_PCR_PE(1) | PORT_PCR_PS(0); 

	SIM->SCGC5 |= SIM_SCGC5_PORTA(1);
	SIM->SCGC6 |= SIM_SCGC6_TPM0(1);
	//PORTA->PCR[2] = PORT_PCR_MUX(3);
	PORTA->PCR[4] = PORT_PCR_MUX(3);
	
	TPM2->MOD = 0xFFFF;
	TPM2->CONTROLS[0].CnSC |= TPM_CnSC_MSB(1) | TPM_CnSC_ELSA(1); // for ch0
  TPM2->CONTROLS[1].CnSC |= TPM_CnSC_MSB(1) | TPM_CnSC_ELSA(1); // for ch1	
	TPM2->SC = TPM_SC_CMOD(1); //turn on
	
	TPM0->MOD = 0xFFFF;
	TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB(1) | TPM_CnSC_ELSA(1); // for ch0
	TPM0->SC = TPM_SC_CMOD(1); //turn on
	TPM2->CONTROLS[0].CnV = 0;
	TPM2->CONTROLS[1].CnV = 0xFFFF;
}


//lights
inline void color_pwmcontrol(const uint16_t color)
{
    // Set the channel compare values
    TPM2->CONTROLS[0].CnV = color;
}


inline void color_onoff(const bool c) // this tuns off and on the light by changing color to 0
{
    // Set convenient on values for each color here from 0 to 65535   
		color = 0;

    // Set the channel compare values
    TPM2->CONTROLS[1].CnV = c ? color : 0xFFFF;
}


//water
inline void water_pwmcontrol(const uint16_t water)
{
    // Set the channel compare values
    TPM2->CONTROLS[0].CnV = water;
}

inline void water_onoff(const bool w) // this tuns off and on 
{
    // Set convenient on values for each water here from 0 to 65535   
    water = 2*1024;

    // Set the channel compare values
    TPM2->CONTROLS[0].CnV = w ? water : 0;

}



//fan
inline void fan_pwmcontrol(const uint16_t fan)
{
    // Set the channel compare values
    TPM2->CONTROLS[0].CnV = fan;
}


inline void fan_onoff(const bool f) // this tuns off and on 
{
    // Set convenient on values for each fan here from 0 to 65535   
    fan = 0xFFFF;

    // Set the channel compare values
    TPM0->CONTROLS[1].CnV = f ? 0 : fan;
}

void heater_onoff(const bool f)
{
	if (f)
	{
		PTA->PSOR |= (1<<1);
	}
	else
		{
			PTA->PCOR |= (1<<1);
		}
		
}
