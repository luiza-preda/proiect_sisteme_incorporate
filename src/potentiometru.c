#include "drivers/gpio/gpio.h"
#include "drivers/pwm/pwm.h"
#include "bsp/nano.h"
#include "drivers/adc/adc.h"

/*
Testare control servomotor in functie de valoarea data de un potentiometru
Valoarea data de potentiometru este vizulalizata in acelasi timp si prin conectarea unui led
*/

int main(void)
{  
    
    PWM_Init(D9,50);
    ADC_Init();
    uint16_t value;
    uint8_t duty;

   while(1)
   {

    value=ADC_Read(0);
    duty=value>>2;
   
    PWM_SetDutyCycle(D9,duty);

   }
}