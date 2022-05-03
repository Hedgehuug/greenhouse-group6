#ifndef UART0_H
#define UART0_H

#include <stdint.h>
#include <MKL25Z4.H>
#include "queue.h"

void uart0_init(void);
uint32_t uart0_num_rx_chars_available(void);
char uart0_get_char(void);
void uart0_put_char(char c);
void uart0_send_string(char *str);

#endif
