#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <avr/io.h>

void I2C_Init(void);
void I2C_Start(uint8_t addr);
void I2C_Write(uint8_t data);
void I2C_Stop(void);

#endif