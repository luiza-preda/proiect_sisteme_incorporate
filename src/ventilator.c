#include "drivers/gpio/gpio.h"
#include "drivers/pwm/pwm.h"
#include "bsp/nano.h"
#include "drivers/adc/adc.h"

int main(void)
{
GPIO_Init(D5,GPIO_OUTPUT); 
GPIO_Init(D10,GPIO_OUTPUT); //direction pin
GPIO_Init(D11,GPIO_OUTPUT); //direction pin 
PWM_Init(D5,2000); //speed pin
uint8_t duty=255; 




    while(1)
    {
    GPIO_Write(D10,GPIO_LOW);
    GPIO_Write(D11,GPIO_HIGH);
    PWM_SetDutyCycle(D5,duty);
    

    }
}