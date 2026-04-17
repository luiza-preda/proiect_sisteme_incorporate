#include "drivers/gpio/gpio.h"
#include "drivers/pwm/pwm.h"
#include "bsp/nano.h"
#include "drivers/adc/adc.h"
#include "utils/delay.h"


//edded up using a passive buzzer, the active buzzer not working 
//needs fixing the tone 
//insted off working with delay_ms we need to use microseconds

int main(void)
{   uint8_t buzztime=1;
    uint8_t buzztime2=1;
    GPIO_Init(D12,GPIO_OUTPUT);

    while(1)
    {
        GPIO_Write(D12,GPIO_HIGH);
        Delay(buzztime2);
        GPIO_Write(D12,GPIO_LOW);
        Delay(buzztime2);
    }

}