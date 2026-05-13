#include "usart.h"
/*
 the formula that calculates the  baud rate => FOSC/16/BAUD-1
 From the datasheet :
 BAUD = 57600 -> USART_Init(16);
 BAUD = 115200 -> USART_Init(8);
*/

void USART_Init(unsigned int ubrr)
{
/*Set baud rate */
UBRR0H = (unsigned char)(ubrr>>8);
UBRR0L = (unsigned char)ubrr;
/*Enable receiver and transmitter */
UCSR0B = (1<<RXEN0)|(1<<TXEN0);
/* Set frame format: 8data, 2stop bit */
UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}


void USART_Transmit(const uint8_t * data, uint8_t len)
{
    const uint8_t *end;

    for (end = data + len; data != end; data++)
    {
        while (!(UCSR0A & (1<<UDRE0))); // wait for every byte
        UDR0 = *data;
    }
}


unsigned char USART_Receive(void)
{
/* Wait for data to be received */
while (!(UCSR0A & (1<<RXC0)))
;
/* Get and return received data from buffer */
return UDR0;
}



void USART_Flush(void)
{
    unsigned char dummy;

    while (UCSR0A & (1 << RXC0))
    {
        dummy = UDR0;
    }

    (void)dummy;
}
