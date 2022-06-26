#ifndef TPM0_H
#define TPM0_H


#include <MKL25Z4.h>

#include <stdbool.h>

void timer0init(void);

void timerStart(void);

unsigned int timerStop(void);


#endif // TPM0_H
