
#include "i2c.h"


#define F_CPU 16000000UL
#define SCL_CLOCK 100000UL


#define START         0x08
#define MT_SLA_ACK    0x18
#define MT_DATA_ACK   0x28



void ERROR(void)
{
  
    while(1);
}


void I2C_Init(void)
{
    // Prescaler = 1
    TWSR = 0x00;

    // Set FREQ I2C 
    TWBR = ((F_CPU / SCL_CLOCK) - 16) / 2;

    // Enable TWI
    TWCR = (1 << TWEN);
}


void I2C_Start(uint8_t addr)
{
    //  START
    TWCR = (1 << TWINT) |(1 << TWSTA) | (1 << TWEN);

    // What to finish 
    while (!(TWCR & (1 << TWINT)));

    // VCheck status
    if ((TWSR & 0xF8) != START)
        ERROR();
    //Slave adress
    TWDR = addr;
    TWCR = (1<<TWINT) |(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));

    if ((TWSR & 0xF8) != MT_SLA_ACK)
        ERROR();
}



void I2C_Stop(void)
{
    TWCR = (1 << TWINT) |(1 << TWEN)  | (1 << TWSTO);

    // what for the magistral 
    while (TWCR & (1 << TWSTO));
}


void I2C_Write(uint8_t data)
{
    // data
    TWDR = data;

    // start transmision 
    TWCR = (1 << TWINT) |(1 << TWEN);

    // shait transmision 
    while (!(TWCR & (1 << TWINT)));

    // check ack 
    if ((TWSR & 0xF8) != MT_DATA_ACK)
        ERROR();
}