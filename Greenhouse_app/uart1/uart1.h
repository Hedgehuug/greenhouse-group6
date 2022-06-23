#ifndef UART1_H
#define UART1_H

#include <stdint.h>
#include <MKL25Z4.H>
#include "../queue/queue.h"

extern queue_t TxQ, RxQ;

void uart1_init(void);
uint32_t uart1_num_rx_chars_available(void);
char uart1_get_char(void);
void uart1_put_char(char c);
void uart1_send_string(char *str);

#endif
