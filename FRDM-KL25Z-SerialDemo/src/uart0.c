#include "UART0.h"

queue_t TxQ, RxQ;

void uart0_init(void)
{  
    // enable clock to UART and Port A
    SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

    // Set UART clock to 48 MHz
    SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
    SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
  
    // select UART pins
    PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);
    PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);
  
    UART0->C2 &=  ~(UARTLP_C2_TE_MASK | UARTLP_C2_RE_MASK);
        
    // Set baud rate to baud rate
    uint32_t divisor = 480000UL/(1152*16);
    UART0->BDH = UART_BDH_SBR(divisor>>8);
    UART0->BDL = UART_BDL_SBR(divisor);
    
    // No parity, 8 bits, one stop bit, other settings;
    UART0->C1 = 0; 
    UART0->S2 = 0;
    UART0->C3 = 0;
    
    // Enable transmitter and receiver but not interrupts
    UART0->C2 = UART_C2_TE_MASK | UART_C2_RE_MASK;
    
    NVIC_SetPriority(UART0_IRQn, 128); // 0, 64, 128 or 192
    NVIC_ClearPendingIRQ(UART0_IRQn); 
    NVIC_EnableIRQ(UART0_IRQn);

    UART0->C2 |= UART_C2_RIE_MASK;
    
    q_init(&TxQ);
    q_init(&RxQ);  
}

void UART0_IRQHandler(void)
{
    uint8_t c;
  
    NVIC_ClearPendingIRQ(UART0_IRQn);
  
    if (UART0->S1 & UART_S1_TDRE_MASK)
    {
        // can send another character
        if(q_dequeue(&TxQ, &c))
        {
            UART0->D = c;
        } 
        else
        {
            // queue is empty so disable transmitter
            UART0->C2 &= ~UART_C2_TIE_MASK;
        }
    }
    if (UART0->S1 & UART_S1_RDRF_MASK)
    {
        c = UART0->D;
        
        if(!q_enqueue(&RxQ, c))
        {
            // error - queue full.
            while (1)
            {;}
        }
    }
    if (UART0->S1 & (UART_S1_OR_MASK | UART_S1_NF_MASK | 
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
    if (!(UART0->C2 & UART_C2_TIE_MASK)) 
    {
        UART0->C2 |= UART_C2_TIE_MASK;
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
    if (!(UART0->C2 & UART_C2_TIE_MASK)) 
    {
        UART0->C2 |= UART_C2_TIE_MASK;
    }        
}
