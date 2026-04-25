#include "drivers/gpio/gpio.h"
#include "drivers/pwm/pwm.h"
#include "bsp/nano.h"
#include "drivers/adc/adc.h"
#include <util/delay.h>
#define D9 GPIO_PORTB, 1

int main(void)
{
    PWM_Init(D9, 50);   
    ADC_Init();

    uint16_t adc_value;
    uint8_t duty;

    while(1)
    {
        adc_value = ADC_Read(4);   

       
      duty = (adc_value * 100) / 1023;
        
       PWM_SetDutyCycle(D9, duty);  

        _delay_ms(20);
    }
}