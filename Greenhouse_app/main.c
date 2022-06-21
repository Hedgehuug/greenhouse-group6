
// Main header that has all other headers imported
#include "controlHeader.h"

void init_DAC()
{
	SIM->SCGC5 = SIM_SCGC5_PORTB_MASK; //Enable clock for PORTB
	SIM->SCGC6 |= (1UL << SIM_SCGC6_ADC0_SHIFT);
	
	ADC0->CFG1 = 0x9C;
}


// Global Variables
struct DHT dht11;

int dataBits[40];
uint8_t dataBytes[5];

// Function Prototypes
static void delay_us(uint32_t d);


// HOPEFULLY TEMPORARY ----- SETTING UP EXTERN VARIABLES MADE IN LIGHTS.C
uint16_t color = 1024;
uint16_t water = 1024;
uint16_t fan = 1024;


// Move to header file
// Gets updated by the sensors, used to trigger activation functions
volatile bool trigger_flags[8] = {0,0,0,0,0,0,0,0};
// Shows current status of actuators, used for cross-reference with trigger_flags
volatile bool status_flags[8] = {0,0,0,0,0,0,0,0};
// To-do:
// Get header file reference because uVision doesn't set it up for us

int main(void)
{
	init_DAC();
	PORTB->PCR[0] = PORT_PCR_MUX(1);
	PORTB->PCR[1] = PORT_PCR_MUX(1);
	// Result of the check
	volatile unsigned res = 0;
	// Initialise timers
	tpm_init();
	
	// Initialise Uart0
	uart0_init();
	// Starting string for UART
	uart0_send_string("DHT Capture\r\n");
	// TPM1 Setup, NOT TPM0
	timer0init();

	// Enables timer to PORTA
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	while(1)
	{
		delay_us(2000000);
		
    PORTA->PCR[1] = 256;
	
    //configure the pin as an output
    PTA->PDDR |= MASK(1);
    //write the pin you're using as output and put it low ( to 0) for 18milliseconds
    PTA->PCOR |= MASK(1);
    delay_us(18000);

    // then write it as HIGH (to 1) for 40 microseconds
    PTA->PDOR |= MASK(1);
    //delay_us(40);
		
		//STEP 3: Pull HIGH and switch to input mode
		//pull-up will pull it HIGH after switching to input mode.
		//PORTA->PCR[1] = 0b00100000011;
    PTA->PDDR &= ~MASK(1); //set to input
		//PORTA->PCR[1] = 0b00100000011;
		
		//STEP 4: Wait between 20 to 40us for sensor to respond
		
//		timerStart();
//		while((PTA->PDIR & MASK(1)) != 0)
//		{
//			if(TPM0->CNT > 80) break; //Timeout
//		}
//	  unsigned int time = timerStop();
//		
//		if(time < 40 || time > 80) 
//		{ 
//			return 0;
//		}
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
				uart0_send_string("error\r\n");
				break;
			}
		}
		
//		for(int i=0; i < 40; i++)
//		{
//			char str[32];
//			sprintf(str,"%d\r\n", dataBits[i]);
//			uart0_send_string(str);
//		}
		
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
		dht11.humidity = dataBytes[0];
		dht11.temperature = dataBytes[2];
		
		char str[32], str2[32];
		
		sprintf(str,"hum = %d\r\n", dht11.humidity);
		sprintf(str2,"temp = %d\r\n", dht11.temperature);
		
		uart0_send_string(str);
		uart0_send_string(str2);
		
		
		//STEP8: Wait for atleast 1-2 second before probing again
	}
	
	/*
	-----CODE FOR LDR TESTING
	while (1){
		ADC0->SC1[0] = 0x03;
		
		while (! (ADC0->SC1[0] & ADC_SC1_COCO_MASK))
		{;}
			
		res = ADC0->R[0];
		if (res > 50000){
		PTB->PDDR &= ~(1<<0);
		}
		else
		{
			PTB->PDDR |= (1<<0);
		}
		
		
		if (res > 35000){
		PTB->PDDR &= ~(1<<1);
		}
		else
		{
			PTB->PDDR |= (1<<1);
		}
			
			
			
		}
		*/
	return 0;
}


/*
-------MAIN FILE FROM DHT11
//main

//Function Prototypes

struct DHT dht11;

static void delay_us(uint32_t d);


// We're using PTA1 as the Pin
//static volatile uint32_t count;

//global variables

struct DHT dht11;

int dataBits[40];
uint8_t dataBytes[5];
	
int main(void)
{	
	uart0_init();
	
	uart0_send_string("DHT Capture\r\n");
	
	timer0init();
	
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
	while(1)
	{
		delay_us(2000000);
		
    PORTA->PCR[1] = 256;
	
    //configure the pin as an output
    PTA->PDDR |= MASK(1);
    //write the pin you're using as output and put it low ( to 0) for 18milliseconds
    PTA->PCOR |= MASK(1);
    delay_us(18000);

    // then write it as HIGH (to 1) for 40 microseconds
    PTA->PDOR |= MASK(1);
    //delay_us(40);
		
		//STEP 3: Pull HIGH and switch to input mode
		//pull-up will pull it HIGH after switching to input mode.
		//PORTA->PCR[1] = 0b00100000011;
    PTA->PDDR &= ~MASK(1); //set to input
		//PORTA->PCR[1] = 0b00100000011;
		
		//STEP 4: Wait between 20 to 40us for sensor to respond
		
//		timerStart();
//		while((PTA->PDIR & MASK(1)) != 0)
//		{
//			if(TPM0->CNT > 80) break; //Timeout
//		}
//	  unsigned int time = timerStop();
//		
//		if(time < 40 || time > 80) 
//		{ 
//			return 0;
//		}
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
				uart0_send_string("error\r\n");
				break;
			}
		}
		
//		for(int i=0; i < 40; i++)
//		{
//			char str[32];
//			sprintf(str,"%d\r\n", dataBits[i]);
//			uart0_send_string(str);
//		}
		
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
		dht11.humidity = dataBytes[0];
		dht11.temperature = dataBytes[2];
		
		char str[32], str2[32];
		
		sprintf(str,"hum = %d\r\n", dht11.humidity);
		sprintf(str2,"temp = %d\r\n", dht11.temperature);
		
		uart0_send_string(str);
		uart0_send_string(str2);
		
		
		//STEP8: Wait for atleast 1-2 second before probing again
	}
}

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


*/


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