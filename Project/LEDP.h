#ifndef TPM2_H
#define TPM2_H

#include <MKL25Z4.H>
#include <stdbool.h>

void tpm_init(void);
void color_onoff(const bool c);
void color_pwmcontrol(const uint16_t color);

void heat_onoff(const bool h);
void heat_pwmcontrol(const uint16_t heat);

void fan_onoff(const bool f);
void fan_pwmcontrol(const uint16_t fan);

#endif // TPM2_H