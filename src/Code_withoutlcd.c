#include "drivers/gpio/gpio.h"
#include "bsp/nano.h"
#include "utils/delay.h"
#include "drivers/adc/adc.h"
#include "drivers/usart/usart.h"
#include "drivers/pwm/pwm.h"
#include <stdio.h>
#include <string.h>


void clear()
{
   GPIO_Write(D2,GPIO_LOW);//a
   GPIO_Write(D6,GPIO_LOW);//b
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
        GPIO_Write(D6,GPIO_HIGH);//b
        GPIO_Write(D4,GPIO_HIGH);//c
        GPIO_Write(D5,GPIO_HIGH);//d
        GPIO_Write(D7,GPIO_HIGH);//e
        GPIO_Write(D8,GPIO_HIGH);//f

        break;
    

        case 1:
        GPIO_Write(D6,GPIO_HIGH);//b
        GPIO_Write(D4,GPIO_HIGH);//c
        break;

        case 2:
        GPIO_Write(D2,GPIO_HIGH);//a
        GPIO_Write(D6,GPIO_HIGH);//b
        GPIO_Write(D5,GPIO_HIGH);//d
        GPIO_Write(D7,GPIO_HIGH);//e
        GPIO_Write(D12,GPIO_HIGH);//g
        break;

        case 3:
        GPIO_Write(D2,GPIO_HIGH);//a
        GPIO_Write(D6,GPIO_HIGH);//b
        GPIO_Write(D4,GPIO_HIGH);//c
        GPIO_Write(D5,GPIO_HIGH);//d
        GPIO_Write(D12,GPIO_HIGH);//g
        break;

        case 4:
        GPIO_Write(D6,GPIO_HIGH);//b
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
        GPIO_Write(D6,GPIO_HIGH);//b
        GPIO_Write(D4,GPIO_HIGH);//c
        break;

        case 8:
        GPIO_Write(D2,GPIO_HIGH);//a
        GPIO_Write(D6,GPIO_HIGH);//b
        GPIO_Write(D4,GPIO_HIGH);//c
        GPIO_Write(D5,GPIO_HIGH);//d
        GPIO_Write(D7,GPIO_HIGH);//e
        GPIO_Write(D8,GPIO_HIGH);//f
        GPIO_Write(D12,GPIO_HIGH);//g
        break;

        case 9:
        GPIO_Write(D2,GPIO_HIGH);//a
        GPIO_Write(D6,GPIO_HIGH);//b
        GPIO_Write(D4,GPIO_HIGH);//c
        GPIO_Write(D5,GPIO_HIGH);//d
        GPIO_Write(D8,GPIO_HIGH);//f
        GPIO_Write(D12,GPIO_HIGH);//g
        break;
    }
}

void afisare(uint16_t valoare)
{
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


}

int main(void)
{
    // INIT pini
    GPIO_Init(D2,GPIO_OUTPUT);//a
    GPIO_Init(D6,GPIO_OUTPUT);//b
    GPIO_Init(D4,GPIO_OUTPUT);//c
    GPIO_Init(D5,GPIO_OUTPUT);//d
    GPIO_Init(D7,GPIO_OUTPUT);//e
    GPIO_Init(D8,GPIO_OUTPUT);//f
    GPIO_Init(D12,GPIO_OUTPUT);//g


    ADC_Init();
    USART_Init(16);
    uint16_t valoare;
    uint16_t temp_inside;
    uint16_t temp_outside;
    uint8_t outside_temperature;
    uint16_t val1;
    uint16_t val2;
    uint8_t duty1=0;
    uint8_t duty2=0;
    char buffer[100];
    char buffer1[100];
    uint8_t inside_temeperature = 0;


    PWM_Init(D9,50);




    while(1)
    { 
        
            valoare = ADC_Read(7);
            temp_inside = ADC_Read(6);
            temp_outside = ADC_Read(3);
            afisare(valoare);
            

static uint8_t pozitie = 90; // pozitia initiala servo

val1 = ADC_Read(2); // axa X joystick
val2 = ADC_Read(1); // axa Y joystick

// viteza miscarii
uint16_t viteza = (val2 / 4) + 1;

// joystick stanga
if(val1 < 400)
{
    if(pozitie > 5)
    {
        pozitie--;
    }
}

// joystick dreapta
else if(val1 > 600)
{
    if(pozitie < 175)
    {
        pozitie++;
    }
}

// mapare unghi -> duty cycle
uint8_t duty = 5 + (pozitie * 20) / 180;

// trimite la servo
PWM_SetDutyCycle(D9, duty);

// viteza miscarii depinde de joystick
Delay(255 - viteza);

 outside_temperature = temp_outside / 10;

        // TEMPERATURA MARE
        if(outside_temperature > 45)
        {
            sprintf(buffer1, "Temperatura ridicata!\n");
            USART_Transmit((uint8_t*)buffer1 ,strlen(buffer1));
            PWM_Init(D3, 1500);

            PWM_SetDutyCycle(D3, 128);
            Delay(50);

            PWM_SetDutyCycle(D3, 0);
            Delay(50);
        }

        // TEMPERATURA MICA
        else if(outside_temperature < 4)
        {
            sprintf(buffer1, "Temperatura scazuta!\n");
            USART_Transmit((uint8_t*)buffer1 ,strlen(buffer1));
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

    inside_temeperature =  (temp_inside/10) - ((1023 - val1)/100) + (valoare/100) ;
        
   

            sprintf(buffer,"Val: %d  %d   %d  %d  %d : %d \n", valoare, temp_inside, temp_outside, val1, val2, inside_temeperature);
            USART_Transmit((uint8_t*)buffer ,strlen(buffer));
            
            Delay(100);
  
            
        
       
    }
}