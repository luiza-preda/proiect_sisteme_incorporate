#include "drivers/gpio/gpio.h"
#include "drivers/pwm/pwm.h"
#include "bsp/nano.h"
#include "drivers/adc/adc.h"
#include "utils/delay.h"

/*
RGB LED
Pin Conections and components used:
- 1 rgb led - that has for pins
- 3 220 ohms resistors

The longest pin is connectedto GND
The singel pin below the GND is connected to the resistence and D10
The first pin above the GND is connected to the resistence and D11
The last pin is connected to the resistence and D12

***
Added potentiometer to A1
the value from the potentiometer is kept in valoare_adc


 
*/

int main(void)
{ 
    GPIO_Init(D10,GPIO_OUTPUT); //RED
    GPIO_Init(D11,GPIO_OUTPUT); //GREEN 
    GPIO_Init(D12,GPIO_OUTPUT); //GREEN 
    ADC_Init();
    uint16_t valoare_adc=0; //if the values are not read from the adc
    
    

    while(1)
    {   
        valoare_adc=ADC_Read(1);// we first read the values from the potetiometer 
// because the values are not stable we are adding an error of 5 to keep the leds off 
        if(valoare_adc<5){
        GPIO_Write(D10,GPIO_LOW);
        GPIO_Write(D11,GPIO_LOW);
        GPIO_Write(D12,GPIO_LOW);
        }
        
        if(valoare_adc<341 && valoare_adc>5){
//red
        GPIO_Write(D10,GPIO_HIGH);
        GPIO_Write(D11,GPIO_LOW);
        GPIO_Write(D12,GPIO_LOW);
        
        }
        if(valoare_adc>= 341 && valoare_adc<682){
//green
        GPIO_Write(D10,GPIO_LOW);
        GPIO_Write(D11,GPIO_HIGH);
        GPIO_Write(D12,GPIO_LOW);

        }
        if(valoare_adc>=682){
//blue
        GPIO_Write(D10,GPIO_LOW);
        GPIO_Write(D11,GPIO_LOW);
        GPIO_Write(D12,GPIO_HIGH);

        
        }

    
}
}
