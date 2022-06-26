#include "DHT11.h"



static void delay_us(uint32_t d)
{

#if (CLOCK_SETUP != 1)
#warning This delay function does not work as designed
#endif

    volatile uint32_t t;

    for(t=4*d; t>0; t--)
    {
        __asm("nop");
        __asm("nop");
    }
}

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
		uart1_send_string("check response error\r\n");
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

DHT_type dht_function()
{
	int dataBits[40];
	uint8_t dataBytes[5];
	DHT_type result;
	PORTA->PCR[1] = 256;
	
    //configure the pin as an output
    PTA->PDDR |= MASK(1);
    //write the pin you're using as output and put it low ( to 0) for 18milliseconds
    PTA->PCOR |= MASK(1);
    delay_us(18000);

    // then write it as HIGH (to 1) for 40 microseconds
    PTA->PDOR |= MASK(1);

		
		//STEP 3: Pull HIGH and switch to input mode
		//pull-up will pull it HIGH after switching to input mode.
    PTA->PDDR &= ~MASK(1); //set to input
		
		//STEP 4: Wait between 20 to 40us for sensor to respond
		
		while(PTA->PDIR & MASK(1)){
			;
		}
		
		//STEP 5: Check for 80us LOW followed by 80us HIGH
		checkResponse(240,30,LOW);
		checkResponse(240,30,HIGH);
		
		//After this DHT sends data. Each bit has a preceding 50us LOW. After which 26-28us means '0' and 70us means '1'
		
		//STEP 6: Fetch data
		int data;

		
		for(int i=0; i < 40; i++)
		{
			data = getDataBit();
			
			dataBits[i] = data;
			
			
			if(data == 0 || data == 1)
			{
				dataBits[i] = data;
			}
			else{
				uart1_send_string("error\r\n");
				break;
			}
		}

		
		//STEP 7: Extract data bytes from array
		data = 0;
		for(int i=0; i<5; i++) // i is the BYTE counter
		{
			for(int j=0; j<8; j++) // j gives the current position of a bit in i'th BYTE
			{
				if( dataBits[ 8*i + j ] )
					data |= (1<<(7-j)); //we need to only shift 1's by ([BYTESZIE-1] - bitLocation) = (7-j)
			}
			dataBytes[i] = data;
			data = 0;
		}
		result.humidity = dataBytes[0];
		result.temperature = dataBytes[2];
	
	return result;
}