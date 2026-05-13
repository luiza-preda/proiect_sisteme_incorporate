#include "drivers/gpio/gpio.h"
#include "drivers/timer/timer0.h"
#include "bsp/nano.h"
#include "drivers/usart/usart.h"
#include <stdio.h>
#include <string.h>
#include "utils/delay.h"
#include "drivers/adc/adc.h"

/*
#define FOSC 1843200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
*/

int main(void)
{ 
    
    USART_Init(8); 
    ADC_Init();

    char buffer[100];
    uint16_t val = 0;
    while(1)
    {
        val = ADC_Read(0);
        sprintf(buffer,"Valoarea este: %d\n", val);
        USART_Transmit((uint8_t*)buffer ,strlen(buffer));
        Delay(100);

        
    }
}
