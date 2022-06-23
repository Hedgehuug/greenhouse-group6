#include "UART0.h"

queue_t TxQ, RxQ;

void uart0_init(void)
{  
    // enable clock to UART and Port A
    SIM->SCGC4 |= SIM_SCGC4_UART1_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

    // Set UART clock to 48 MHz
    SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
    SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
  
    // select UART pins
    PORTE->PCR[0] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(3);
    PORTE->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(3);
  
    UART1->C2 &=  ~(UARTLP_C2_TE_MASK | UARTLP_C2_RE_MASK);
        
    // Set baud rate to baud rate
    uint32_t divisor = 240000UL/(96*16);
    UART1->BDH = UART_BDH_SBR(divisor>>8);
    UART1->BDL = UART_BDL_SBR(divisor);
    
    // No parity, 8 bits, one stop bit, other settings;
    UART1->C1 = 0; 
    UART1->S2 = 0;
    UART1->C3 = 0;
    
    // Enable transmitter and receiver but not interrupts
    UART1->C2 = UART_C2_TE_MASK | UART_C2_RE_MASK;
    
    NVIC_SetPriority(UART1_IRQn, 128); // 0, 64, 128 or 192
    NVIC_ClearPendingIRQ(UART1_IRQn); 
    NVIC_EnableIRQ(UART1_IRQn);

    UART1->C2 |= UART_C2_RIE_MASK;
    
    q_init(&TxQ);
    q_init(&RxQ);  
}

void UART1_IRQHandler(void)
{
    uint8_t c;
  
    NVIC_ClearPendingIRQ(UART1_IRQn);
  
    if (UART1->S1 & UART_S1_TDRE_MASK)
    {
        // can send another character
        if(q_dequeue(&TxQ, &c))
        {
            UART1->D = c;
        } 
        else
        {
            // queue is empty so disable transmitter
            UART1->C2 &= ~UART_C2_TIE_MASK;
        }
    }
    if (UART1->S1 & UART_S1_RDRF_MASK)
    {
        c = UART1->D;
        
        if(!q_enqueue(&RxQ, c))
        {
            // error - queue full.
            while (1)
            {;}
        }
    }
    if (UART1->S1 & (UART_S1_OR_MASK | UART_S1_NF_MASK | 
                     UART_S1_FE_MASK | UART_S1_PF_MASK))
    {
        // handle the error
        // clear the flag
        /*
        UART0->S1 = UART_S1_OR_MASK | UART_S1_NF_MASK | 
            UART_S1_FE_MASK | UART_S1_PF_MASK;
        */
    }
}

void uart0_send_string(char * str)
{   
    // Enqueue string
    while (*str != '\0') 
    { 
        // Wait for space to open up
        while(!q_enqueue(&TxQ, *str))
        {;}
            
        str++;
    }
    
    // Start transmitter if it isn't already running
    if (!(UART1->C2 & UART_C2_TIE_MASK)) 
    {
        UART1->C2 |= UART_C2_TIE_MASK;
    }
}

uint32_t uart0_num_rx_chars_available(void)
{
    return q_size(&RxQ);
}

char uart0_get_char(void) 
{
    uint8_t c=0;
    
    // Wait for data.
    // If waiting is not desired, call the function
    // uart1_num_rx_chars_available() first to make sure data is available.
    while(!q_dequeue(&RxQ, &c))
    {;}
    
    return (char)c;
}

void uart0_put_char(char c) 
{
    // Wait for space to open up
    while(!q_enqueue(&TxQ, c))
    {;}
            
    // Start transmitter if it isn't already running
    if (!(UART1->C2 & UART_C2_TIE_MASK)) 
    {
        UART1->C2 |= UART_C2_TIE_MASK;
    }        
}
