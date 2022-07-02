
// Main header that has all other headers imported
#include "controlHeader.h"

void init_DAC()
{
	SIM->SCGC5 = SIM_SCGC5_PORTB_MASK; //Enable clock for PORTB
	SIM->SCGC6 |= (1UL << SIM_SCGC6_ADC0_SHIFT);
	
	ADC0->CFG1 = 0x9C;
}
uint16_t checkAnalog(int channel)
{
	ADC0->SC1[0] = channel;
	
	while (! (ADC0->SC1[0] & ADC_SC1_COCO_MASK))
	{;}
		
	uint16_t res = ADC0->R[0];
	return res;
}




// Global Variables
DHT_type dht11;

// Global Sensor Values
uint16_t LDR_value;					// LDR Level
uint16_t SoilMoisture;			// Soil Moisture Level


// Global Setting values
int heaterTemp = 20;
int fanTemp = 29;
int soilMoistTrigger = 2000;
int lightTrigger = 55000;
char localReceive[32];

//int dataBits[40];
//uint8_t dataBytes[5];

// Function Prototypes
static void delay_us(uint32_t d);

//static void delay_m(uint32_t d);

void displayLCD(int val, int val2);

//void I2C_Write_byt(uint8_t addr, uint8_t *send_data, uint8_t send_data_len){
//	
//	i2c_WriteText(I2C0, addr, send_data_len, send_data);
//}

//void delay_MS(uint16_t time){
//	delay_m(time);
//}


// HOPEFULLY TEMPORARY ----- SETTING UP EXTERN VARIABLES MADE IN LIGHTS.C
uint16_t color = 1024;
uint16_t water = 1024;
uint16_t fan = 1024;


#define FLAG_LENGTH 5
#define HEATER_FLAG 0
#define FAN_FLAG 1
#define PUMP_FLAG 2
#define LIGHT_FLAG 3


// Move to header file
// Gets updated by the sensors, used to trigger activation functions
volatile bool trigger_flags[8] = {0,0,0,0,0,0,0,0};
// Shows current status of actuators, used for cross-reference with trigger_flags
volatile int status_flags[FLAG_LENGTH];
// To-do:
// Get header file reference because uVision doesn't set it up for us


// TEST CODE -------------------------------
int loop_counter = 0;
char str[32], str2[32], str3[32];
int main(void)
{
	init_DAC();
	PORTB->PCR[0] = PORT_PCR_MUX(1);
	PORTB->PCR[1] = PORT_PCR_MUX(1);
	
	//i2c_Init(I2C0, ALT3, MULT1, 0x1F);// 100KHz = (48MHz / (2 * 240)) 
	
	//PCF8574T_Init(0x27, delay_MS, I2C_Write_byt);
	
	//buttonInit();
	
	
	// Result of the check
	volatile unsigned res = 0;
	// Initialise timers
	tpm_init();
	
	// Initialise Uart1
	uart1_init();
	
	// Starting string for UART
	// TPM1 Setup, NOT TPM0
	timer0init();

	// Enables timer to PORTA
	//SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	//PORTA->PCR[1] |= PORT_PCR_MUX(1) | PORT_PCR_PE(1) | PORT_PCR_PS(0);
	int pumpCounter = 0;
	PORTB->PCR[1] |= PORT_PCR_MUX(1);

	while(1)
	{
		delay_us(2000000);
		
		
		
		uart1_receive_string(receiveString);			// Receive data through UART
		

		switch (receiveString[0])
		{
			case 'l':
				
				for (int i = 1; receiveString[i] != '\n'; i++)
			{
				localReceive[i-1] = receiveString[i];
			}
			
			int tempLight = atoi(localReceive);
			lightTrigger = (tempLight*0xFFFF)/100.0;
				break;
			case 't':
				for (int i = 1; receiveString[i] != '\n'; i++)
				{
					localReceive[i-1] = receiveString[i];
				}
				fanTemp = atoi(localReceive);
				break;
			case 'h':
				for (int i = 1; receiveString[i] != '\n'; i++)
				{
					localReceive[i-1] = receiveString[i];
				}
				heaterTemp = atoi(localReceive);
				break;
			default:
				break;
		}
		//sprintf((char *)receiveString,"%c", '\0');
					
			
		
		
		// Fetch Temperature and humidity 
	
		//dht11 = dht_function();
//		
//		sprintf((char *)str,"t%d\n", dht11.temperature);
//		sprintf((char *)str2,"h%d\n", dht11.humidity);
					
	
//		if (loop_counter == 0)
//		{
//			loop_counter++;
//			uart1_send_string(str);
//		}	
//		else if(loop_counter == 1)
//		{
//			loop_counter = 0;
//			uart1_send_string(str2);
//		}
					
		
						
		
		LDR_value = checkAnalog(0);
				sprintf((char *)str,"l%d\n", LDR_value);
		
		SoilMoisture = 0xFFFF - checkAnalog(8);
				sprintf((char *)str2,"s%d\n", SoilMoisture);
		
		
		
		if (loop_counter == 0)
		{
			loop_counter++;
			uart1_send_string(str);
		}	
		else if(loop_counter == 1)
		{
			loop_counter++;
			uart1_send_string(str2);
		}
		else if(loop_counter == 2)
		{
			loop_counter = 0;
			sprintf((char *)str3,"%c", 'a');
			for(int i = 0; i < FLAG_LENGTH; i++)
			{
				sprintf(&str3[i+1],"%d\n", status_flags[i]);
			}
			
			uart1_send_string(str3);
		}
				
		
		// Check LDR Flag
		if (LDR_value >= lightTrigger)
		{
			color_pwmcontrol(0);
			status_flags[LIGHT_FLAG] = 1;
		}
		else{
			status_flags[LIGHT_FLAG] = 0;
			color_pwmcontrol(0xFFFF);
		}
		
		// Check temperature, either enable heater or fan
		if (dht11.temperature >= fanTemp)
		{
			fan_onoff(true);
			status_flags[FAN_FLAG] = 1;
		}
		else
		{
			fan_onoff(false);
			status_flags[FAN_FLAG] = 0;
		}
		
		// Turn on heater if temperature is below desired
		if (dht11.temperature <= heaterTemp)
		{
			heater_onoff(true);
			status_flags[HEATER_FLAG] = 1;
		}
		else
		{
			heater_onoff(false);
			status_flags[HEATER_FLAG] = 0;
		}
		
		
		//(char *)str,"t%d\n", dht11.temperature);
		
		// Check Soil Moisture
		if (SoilMoisture >= soilMoistTrigger && pumpCounter == 0)
		{
			color_onoff(true);
			pumpCounter++;
			status_flags[PUMP_FLAG] = 1;
		}
		else if (pumpCounter >= 2)
		{
			pumpCounter = 0;
			color_onoff(false);
			status_flags[PUMP_FLAG] = 0;
		}
		else if (pumpCounter < 2 && pumpCounter > 0)
		{
			pumpCounter++;
		}
		
		
		//sprintf((char *)str,"hum = %d\r\n", dht11.humidity);
		//sprintf((char *)str2,"temp = %d\r\n", dht11.temperature);
		
		//uart1_send_string(str);
		
//		buttonFunc();
//		displayLCD(heaterTemp, fanTemp);
		
	}
	
	
	return 0;
}



void displayLCD(int val, int val2){
	if(y == 0){
		minX = 0;
		maxX = 0;
		mainScreen(dht11);
		} else{
		minX = 0;
		maxX = 1;
		select(val, val2);
	}
}

static void delay_us(uint32_t d)
{


    volatile uint32_t t;

    for(t=4*d; t>0; t--)
    {
        __asm("nop");
        __asm("nop");
    }
}

//static void delay_m(uint32_t d)
//{

//#if (CLOCK_SETUP != 1)
//#warning This delay function does not work as designed
//#endif

//    volatile uint32_t t;

//    for(t=4000*d; t>0; t--)
//    {
//        __asm("nop");
//        __asm("nop");
//    }
//}