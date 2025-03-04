#include "UART.h"

void Init_UART(void) // This routine is to initialize the UART
{
    OpenUSART(USART_TX_INT_OFF & USART_RX_INT_OFF &
            USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX &
            USART_BRGH_HIGH, 25);
    OSCCON = 0x60;
}

void putch(char c) // This routine must always go with the
// ?Init_UART()?
{
    while (!TRMT);
    TXREG = c;
}
