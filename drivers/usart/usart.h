#ifndef USART_H
#define USART_H

#include <stdint.h>
#include <avr/io.h>


void USART_Init(unsigned int ubrr);
void USART_Transmit(const uint8_t * data, uint8_t len);
unsigned char USART_Receive(void);
void USART_Flush(void);

#endif
