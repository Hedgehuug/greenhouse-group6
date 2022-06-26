#ifndef LCD_H
#define LCD_H

#include <stdio.h>
#include <stdlib.h>
#include <MKL25Z4.H>
#include <stdbool.h>
#include "../Temp/DHT11.h"
#include "../Driver/driver.h"


extern volatile int y;
extern volatile int x[3];
extern volatile int minY;
extern volatile int maxY;
extern volatile int minX;
extern volatile int maxX;

void buttonInit(void);

void callwrite( char string[], int x, uint8_t line);

void mainScreen(struct DHT x);

void Enter(void);

void Undo(void);

void nextSlide(void);

void prevSlide(void);

void select(int value, int value2);

void buttonFunc(void);

#endif
