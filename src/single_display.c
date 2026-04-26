#include "drivers/gpio/gpio.h"
#include "bsp/nano.h"
#include <util/delay.h>

void clear()
{
    GPIO_Write(GPIO_PORTD,7,GPIO_LOW);
    GPIO_Write(GPIO_PORTD,6,GPIO_LOW);
    GPIO_Write(GPIO_PORTD,4,GPIO_LOW);
    GPIO_Write(GPIO_PORTD,3,GPIO_LOW);
    GPIO_Write(GPIO_PORTD,2,GPIO_LOW);
    GPIO_Write(GPIO_PORTB,0,GPIO_LOW);
    GPIO_Write(GPIO_PORTB,1,GPIO_LOW);
}

void display_digit(int d)
{
    clear();

    switch(d)
    {
        case 0:
            GPIO_Write(GPIO_PORTD,7,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,6,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,4,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,3,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,2,GPIO_HIGH);
            GPIO_Write(GPIO_PORTB,0,GPIO_HIGH);
            break;

        case 1:
            GPIO_Write(GPIO_PORTD,6,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,4,GPIO_HIGH);
            break;

        case 2:
            GPIO_Write(GPIO_PORTD,7,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,6,GPIO_HIGH);
            GPIO_Write(GPIO_PORTB,1,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,2,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,3,GPIO_HIGH);
            break;

        case 3:
            GPIO_Write(GPIO_PORTD,7,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,6,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,4,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,3,GPIO_HIGH);
            GPIO_Write(GPIO_PORTB,1,GPIO_HIGH);
            break;

        case 4:
            GPIO_Write(GPIO_PORTD,6,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,4,GPIO_HIGH);
            GPIO_Write(GPIO_PORTB,1,GPIO_HIGH);
            GPIO_Write(GPIO_PORTB,0,GPIO_HIGH);
            break;

        case 5:
            GPIO_Write(GPIO_PORTD,7,GPIO_HIGH);
            GPIO_Write(GPIO_PORTB,0,GPIO_HIGH);
            GPIO_Write(GPIO_PORTB,1,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,4,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,3,GPIO_HIGH);
            break;

        case 6:
            GPIO_Write(GPIO_PORTD,7,GPIO_HIGH);
            GPIO_Write(GPIO_PORTB,0,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,2,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,3,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,4,GPIO_HIGH);
            GPIO_Write(GPIO_PORTB,1,GPIO_HIGH);
            break;

        case 7:
            GPIO_Write(GPIO_PORTD,7,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,6,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,4,GPIO_HIGH);
            break;

        case 8:
            GPIO_Write(GPIO_PORTD,7,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,6,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,4,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,3,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,2,GPIO_HIGH);
            GPIO_Write(GPIO_PORTB,0,GPIO_HIGH);
            GPIO_Write(GPIO_PORTB,1,GPIO_HIGH);
            break;

        case 9:
            GPIO_Write(GPIO_PORTD,7,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,6,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,4,GPIO_HIGH);
            GPIO_Write(GPIO_PORTD,3,GPIO_HIGH);
            GPIO_Write(GPIO_PORTB,0,GPIO_HIGH);
            GPIO_Write(GPIO_PORTB,1,GPIO_HIGH);
            break;
    }
}

int main(void)
{
    // INIT pini
    GPIO_Init(GPIO_PORTD,7,GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTD,6,GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTD,4,GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTD,3,GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTD,2,GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTB,0,GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTB,1,GPIO_OUTPUT);

    while(1)
    {
        for(int i = 0; i <= 9; i++)
        {
            display_digit(i);
            _delay_ms(1000);
        }
    }
}