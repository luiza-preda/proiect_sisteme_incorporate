#include "drivers/gpio/gpio.h"
#include "drivers/pwm/pwm.h"
#include "bsp/nano.h"
#include "utils/delay.h"

int main(void)
{ 
    PWM_Init(D9,50);

    while (1)
    {
       for(int i=12;i<=25;i++)
       {
        PWM_SetDutyCycle(D9,i);
        Delay(200);
       }
       for(int i=25;i>=12;i--)
       {
        PWM_SetDutyCycle(D9,i);
        Delay(200);
       }
        

    }
    
}