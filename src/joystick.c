#include "drivers/gpio/gpio.h"
#include "drivers/pwm/pwm.h"
#include "bsp/nano.h"
#include "drivers/adc/adc.h"

//A5 - x si A4 - y
//0-1023
//servo to d9
//switch to d12
/*
Reading a value from 0 to 1023 from X axis and seding the signal to the servo, transforming it in a 0-255 value
*/

int main(void)
{
    PWM_Init(D9,50);
    PWM_Init(D3,50);
    ADC_Init();
    uint16_t first_value;
    uint8_t first_duty;
    uint16_t second_value;
    uint8_t second_duty;

    while(1)
    {
       first_value=ADC_Read(5);
       second_value=ADC_Read(4);

       first_duty=first_value/4;
       second_duty=second_value/4;
       PWM_SetDutyCycle(D9,first_duty);
       PWM_SetDutyCycle(D3,second_duty);
    }
}