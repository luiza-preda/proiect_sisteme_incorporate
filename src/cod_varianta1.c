#include "drivers/gpio/gpio.h"
#include "bsp/nano.h"
#include "utils/delay.h"
#include "drivers/adc/adc.h"
#include "drivers/usart/usart.h"
#include <stdio.h>
#include <string.h>
#include "drivers/pwm/pwm.h"

void clear()
{
   GPIO_Write(D2,GPIO_LOW);//a
   GPIO_Write(D3,GPIO_LOW);//b
   GPIO_Write(D4,GPIO_LOW);//c
   GPIO_Write(D5,GPIO_LOW);//d
   GPIO_Write(D7,GPIO_LOW);//e
   GPIO_Write(D8,GPIO_LOW);//f
   GPIO_Write(D12,GPIO_LOW);//g
}
void display_digit(int d)
{
    clear();

    switch(d)
    {
        case 0:
    
        GPIO_Write(D2,GPIO_HIGH);//a
        GPIO_Write(D3,GPIO_HIGH);//b
        GPIO_Write(D4,GPIO_HIGH);//c
        GPIO_Write(D5,GPIO_HIGH);//d
        GPIO_Write(D7,GPIO_HIGH);//e
        GPIO_Write(D8,GPIO_HIGH);//f

        break;
    

        case 1:
        GPIO_Write(D3,GPIO_HIGH);//b
        GPIO_Write(D4,GPIO_HIGH);//c
        break;

        case 2:
        GPIO_Write(D2,GPIO_HIGH);//a
        GPIO_Write(D3,GPIO_HIGH);//b
        GPIO_Write(D5,GPIO_HIGH);//d
        GPIO_Write(D7,GPIO_HIGH);//e
        GPIO_Write(D12,GPIO_HIGH);//g
        break;

        case 3:
        GPIO_Write(D2,GPIO_HIGH);//a
        GPIO_Write(D3,GPIO_HIGH);//b
        GPIO_Write(D4,GPIO_HIGH);//c
        GPIO_Write(D5,GPIO_HIGH);//d
        GPIO_Write(D12,GPIO_HIGH);//g
        break;

        case 4:
        GPIO_Write(D3,GPIO_HIGH);//b
        GPIO_Write(D4,GPIO_HIGH);//c
        GPIO_Write(D8,GPIO_HIGH);//f
        GPIO_Write(D12,GPIO_HIGH);//g
        break;

        case 5:
        GPIO_Write(D2,GPIO_HIGH);//a
        GPIO_Write(D4,GPIO_HIGH);//c
        GPIO_Write(D5,GPIO_HIGH);//d
        GPIO_Write(D8,GPIO_HIGH);//f
        GPIO_Write(D12,GPIO_HIGH);//g
        break;

        case 6:
        GPIO_Write(D2,GPIO_HIGH);//a
        GPIO_Write(D4,GPIO_HIGH);//c
        GPIO_Write(D5,GPIO_HIGH);//d
        GPIO_Write(D7,GPIO_HIGH);//e
        GPIO_Write(D8,GPIO_HIGH);//f
        GPIO_Write(D12,GPIO_HIGH);//g
        break;

        case 7:
        GPIO_Write(D2,GPIO_HIGH);//a
        GPIO_Write(D3,GPIO_HIGH);//b
        GPIO_Write(D4,GPIO_HIGH);//c
        break;

        case 8:
        GPIO_Write(D2,GPIO_HIGH);//a
        GPIO_Write(D3,GPIO_HIGH);//b
        GPIO_Write(D4,GPIO_HIGH);//c
        GPIO_Write(D5,GPIO_HIGH);//d
        GPIO_Write(D7,GPIO_HIGH);//e
        GPIO_Write(D8,GPIO_HIGH);//f
        GPIO_Write(D12,GPIO_HIGH);//g
        break;

        case 9:
        GPIO_Write(D2,GPIO_HIGH);//a
        GPIO_Write(D3,GPIO_HIGH);//b
        GPIO_Write(D4,GPIO_HIGH);//c
        GPIO_Write(D5,GPIO_HIGH);//d
        GPIO_Write(D8,GPIO_HIGH);//f
        GPIO_Write(D12,GPIO_HIGH);//g
        break;
    }
}

int main(void)
{
        ADC_Init();
        USART_Init(16);
        GPIO_Init(D9,GPIO_OUTPUT); 
        GPIO_Init(D10,GPIO_OUTPUT); //direction pin
        GPIO_Init(D11,GPIO_OUTPUT); //direction pin 
        PWM_Init(D9,2000); //speed pin
        char buffer[100];
        uint8_t duty1=0; 
        uint8_t duty2=0; 
        uint16_t val1= 0;
        uint16_t val2=0;
        uint16_t valoare;
        uint16_t valoare_p1;
        uint8_t temeratura = 0;


        GPIO_Init(D2,GPIO_OUTPUT);//a
        GPIO_Init(D3,GPIO_OUTPUT);//b
        GPIO_Init(D4,GPIO_OUTPUT);//c
        GPIO_Init(D5,GPIO_OUTPUT);//d
        GPIO_Init(D7,GPIO_OUTPUT);//e
        GPIO_Init(D8,GPIO_OUTPUT);//f
        GPIO_Init(D12,GPIO_OUTPUT);//g

    while(1)
    {
        
            valoare = ADC_Read(2);


            if(valoare>0 && valoare<102)
            {
                display_digit(0);
            }

            if(valoare>=102 && valoare<204)
            {
                display_digit(1);
            }
            if(valoare>=204 && valoare<306)
            {
                display_digit(2);
            }
            if(valoare>=306 && valoare<408)
            {
                display_digit(3);
            }
            if(valoare>=408 && valoare<510)
            {
                display_digit(4);
            }
            if(valoare>=510 && valoare<612)
            {
                display_digit(5);
            }
            if(valoare>=612 && valoare<714)
            {
                display_digit(6);
            }
            if(valoare>=714 && valoare<816)
            {
                display_digit(7);
            }
            if(valoare>=816 && valoare<918)
            {
                display_digit(8);
            }
            if(valoare>=918 && valoare<1023)
            {
                display_digit(9);
            }

    val1 =  ADC_Read(0);
    val2 = ADC_Read(1);
    GPIO_Write(D10,GPIO_LOW);
    GPIO_Write(D11,GPIO_HIGH);

    duty1 = val1/10;
    duty2= val2/10;

    valoare_p1=ADC_Read(3);

    temeratura = valoare_p1/10;

    temeratura = temeratura - (val2/100) + (valoare/100);
    
   // sprintf(buffer,"Valoarea este: %d-%d-%d -%d --- %d \n",val1, val2, duty1, duty2, valoare);
    sprintf(buffer, "Temperatura este: %d si potentiometrul citeste: %d\n", temeratura, valoare_p1);
    USART_Transmit((uint8_t*)buffer ,strlen(buffer));
    
    Delay(100);
    PWM_SetDutyCycle(D9,duty1);
    PWM_SetDutyCycle(D9,duty2);

    }
}