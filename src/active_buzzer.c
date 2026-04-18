#include "drivers/gpio/gpio.h"
#include "utils/delay.h"
#include "drivers/pwm/pwm.h"
#include "bsp/nano.h"
#include "drivers/adc/adc.h"

int main(void)
{
    GPIO_Init(GPIO_PORTB, 4, GPIO_OUTPUT);

    GPIO_Init(GPIO_PORTD, 2, GPIO_INPUT);
    GPIO_Write(GPIO_PORTD, 2, GPIO_HIGH); // pull-up

    int buzzer_on = 0;

    while(1)
    {
        
        if(GPIO_Read(GPIO_PORTD, 2) == GPIO_LOW)
        {
            Delay(20); 

            if(GPIO_Read(GPIO_PORTD, 2) == GPIO_LOW)
            {
                buzzer_on = !buzzer_on; 

                
                while(GPIO_Read(GPIO_PORTD, 2) == GPIO_LOW);
            }
        }

        
        if(buzzer_on)
        {
            GPIO_Write(GPIO_PORTB, 4, GPIO_HIGH);
            Delay(200);

            GPIO_Write(GPIO_PORTB, 4, GPIO_LOW);
            Delay(200);
        }
        else
        {
            GPIO_Write(GPIO_PORTB, 4, GPIO_LOW);
        }
    }
}