#include "drivers/gpio/gpio.h"
#include "drivers/pwm/pwm.h"
#include "drivers/adc/adc.h"
#include "bsp/nano.h"
#include "utils/delay.h"

int main(void)
{
    ADC_Init();

    uint16_t adc_value;
    uint8_t temperature;

    while(1)
    {
        adc_value = ADC_Read(0);

        // 0-1023 -> aproximativ 0-100 grade
        temperature = adc_value / 10;

        // TEMPERATURA MARE
        if(temperature > 45)
        {
            PWM_Init(D3, 1500);

            PWM_SetDutyCycle(D3, 128);
            Delay(50);

            PWM_SetDutyCycle(D3, 0);
            Delay(50);
        }

        // TEMPERATURA MICA
        else if(temperature < 4)
        {
            PWM_Init(D3, 300);

            PWM_SetDutyCycle(D3, 128);
            Delay(300);

            PWM_SetDutyCycle(D3, 0);
            Delay(700);
        }

        // NORMAL
        else
        {
            PWM_SetDutyCycle(D3, 0);
        }
    }
}