#ifndef TPM2_H
#define TPM2_H

#include <MKL25Z4.H>
#include <stdbool.h>

void tpm_init(void);
void color_onoff(const bool c);
void color_pwmcontrol(const uint16_t color);

void water_onoff(const bool w);
void water_pwmcontrol(const uint16_t water);

void fan_onoff(const bool f);
void fan_pwmcontrol(const uint16_t fan);

extern unsigned ldr_light;

#endif // TPM2_H