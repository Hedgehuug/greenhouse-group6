#ifndef TPM2_H
#define TPM2_H

#include <MKL25Z4.H>
#include <stdbool.h>

void tpm2_init(void);
void color_onoff(const bool c);
void color_pwmcontrol(const uint16_t color);

#endif // TPM2_H