//lcd func
#include "LCD.h"


volatile int y = 0;
volatile int x[3] = {0,0,0};
volatile int minY = 0;
volatile int maxY = 3;
volatile int minX;
volatile int maxX;


void buttonInit(void){
	
	PORTC->PCR[13] |= 0b00100000011;
	PORTC->PCR[12] |= 0b00100000011;
	PORTC->PCR[11] |= 0b00100000011;
	PORTC->PCR[10] |= 0b00100000011;
		
	PTC->PDDR &= ~MASK(13); //set to input
	PTC->PDDR &= ~MASK(12); //set to input
	PTC->PDDR &= ~MASK(11); //set to input
	PTC->PDDR &= ~MASK(10); //set to input
}

void callwrite( char string[], int x, uint8_t line){
	sprintf(string,"%d", x);
	PCF8574T_displayString(string, line);
}

void select(int value, int value2){
	char maxString[16];
	
	char minString[16];
	
	if(y == 1){
		
	if(x[y] > maxX){
		x[y] = minX;
	}
	PCF8574T_displayString("Select:", 1);
	if(x[y] == 0){
		PCF8574T_displayString(">Min Temp", 2);
	}
	if(x[y] == 1){
		PCF8574T_displayString(">Max Temp", 2);
	}
	
	if(y == 2){
			if(x[y-1] == 0){
			minX = 0;
			maxX = 1;
			callwrite( minString, value, 2);
		}
		if(x[y-1] == 1){
			minX = 2;
			maxX = 4;
			callwrite( maxString, value, 2);		
		}
	}
}
}

void mainScreen(struct DHT x, int percent, char str[]){
	
	//first line displays the sensor values
	
	char str1[16];
	
	sprintf(str1,"H %d/T %dC/S %d", x.humidity, x.temperature, percent);
		
	PCF8574T_displayString(str1, 1);
	
	//second line is made for the flags
	
	PCF8574T_displayString(str, 2);
	
}

void Enter(void){
	y++;
	if(y > maxY){
		y = minY;
	}
	x[y] = minX;
	PCF8574T_sendCommand8bit(0b00000001, true); // display clear
}

void Undo(void){
	y--;
	if(y < minY){
		y = minY;
	}
	x[y] = x[y];
	PCF8574T_sendCommand8bit(0b00000001, true); // display clear
}

void nextSlide(void){
	x[y]++;
	if(x[y] > maxX){
		x[y] = minX;
	}
	PCF8574T_sendCommand8bit(0b00000001, true); // display clear
}

void prevSlide(void){
	x[y]--;
	if(x[y] < minX){
		x[y] = minX;
	}
	PCF8574T_sendCommand8bit(0b00000001, true); // display clear
}

void buttonFunc(void){
		if(!(PTC->PDIR & MASK(13))){
			Enter();
		}
		
		if(!(PTC->PDIR & MASK(12))){
			Undo();
		}
		if(!(PTC->PDIR & MASK(11))){
			nextSlide();
		}
		if(!(PTC->PDIR & MASK(10))){
			prevSlide();
		}
	}
