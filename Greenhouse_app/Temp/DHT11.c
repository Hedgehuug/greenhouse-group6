#include "DHT11.h"


void checkResponse(unsigned int waitTimeUS, unsigned int margin, bool pinValue)
{
	int time = 0;
	int maxwait = waitTimeUS + margin;
	
	timerStart();
	if(pinValue)
	{
		while( PTA->PDIR & MASK(1) )
		{
			if( TPM1->CNT > (maxwait)) break; 
		}
	}
	else
	{
		while(!(PTA->PDIR & MASK(1)))
		{
			if(TPM1->CNT > (maxwait)) break; 
		}
	}
	time = timerStop();
	
	if(time < (waitTimeUS - margin) || time > maxwait){
		uart0_send_string("check response error\r\n");
	}	
}

int getDataBit(void)
{
	int time = 0;
	
	int temp;
	
	checkResponse(150,15,LOW); //Each data bit starts with 50us low
	
	timerStart();
	while( PTA->PDIR & MASK(1))
	{
		if( TPM1->CNT > 250)
		{
			//printError("Data Error");
			temp = 2; //2 = Error (Timeout for 50us LOW)
		}
		;
	}
	time = timerStop();
	
	if((time > (80-20)) && (time < (80+20))) //I am getting 21 for HIGH using my DHT11 sensor, so using higher margin
	{
		temp = 0;
	}
	else if((time > (210-15)) && (time < (210+15)))
	{
		temp = 1;
	}
//	else 
//	{ 
//		//printError("Data Error");
//		temp = 2; //Timeout for data pulse 
//	}
	return temp;
}