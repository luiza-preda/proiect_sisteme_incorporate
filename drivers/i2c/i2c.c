/*

#include  "i2c.h"
#include "mocks/avr/io.h"
//#include "utils/twi.h"

#define I2C_FREQ  100000UL
#define TWBR_VAL  ((F_CPU / I2C_FREQ - 16) / 2)

void I2C_Init(void) {
    TWSR = 0x00;         //prescaler = 1 
    TWBR = TWBR_VAL;
    TWCR = (1 << TWEN);  // enable TWI 
}

//Send START condition
TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN)


//Wait for TWINT flag set. This
//indicates that the START
//condition has been transmitted

while (!(TWCR & (1<<TWINT)))
;


//Check value of TWI status
//register. Mask prescaler bits. If
//status different from START go
//to ERROR

if ((TWSR & 0xF8) != START)
ERROR();

//Load SLA_W into TWDR
//register. Clear TWINT bit in
//TWCR to start transmission of
//address

TWDR = SLA_W;
TWCR = (1<<TWINT) | (1<<TWEN);

//Wait for TWINT flag set. This
//indicates that the SLA+W has
//been transmitted, and
//ACK/NACK has been received.

while (!(TWCR & (1<<TWINT)))
;

//Check value of TWI status
//register. Mask prescaler bits. If
//status different from
//MT_SLA_ACK go to ERROR

if ((TWSR & 0xF8) != MT_SLA_ACK)
ERROR();

//Load DATA into TWDR register.
//clear TWINT bit in TWCR to
//start transmission of data

TWDR = DATA;
TWCR = (1<<TWINT) | (1<<TWEN);

//Wait for TWINT flag set. This
//indicates that the DATA has
//been transmitted, and
//ACK/NACK has been received.

while (!(TWCR & (1<<TWINT)))
;

//Check value of TWI status
//register. Mask prescaler bits. If
//status different from
//MT_DATA_ACK go to ERROR

if ((TWSR & 0xF8)!= MT_DATA_ACK)
ERROR();

//Transmit STOP condition
TWCR = (1<<TWINT)|(1<<TWEN)|
(1<<TWSTO);


*/


#include "i2c.h"
//#include <avr/io.h>
//#include <util/twi.h>

/*
 * TWI (I2C) DRIVER — ATmega328P
 *
 * SCL frequency = F_CPU / (16 + 2 * TWBR * prescaler)
 * 100kHz @ 16MHz, prescaler=1: TWBR = (16000000/100000 - 16) / 2 = 72
 */
#include "i2c.h"
//#include "avr/io.h"

#define F_CPU 16000000UL
#define SCL_CLOCK 100000UL

// Status codes
//??? should be in utils/twi.h
#define START         0x08
#define MT_SLA_ACK    0x18
#define MT_DATA_ACK   0x28

// Exemplu adresă slave + Write
//#define SLA_W 0x50

void ERROR(void)
{
    // tratare eroare
    while(1);
}


void I2C_Init(void)
{
    // Prescaler = 1
    TWSR = 0x00;

    // Setare frecvență SCL
    TWBR = ((F_CPU / SCL_CLOCK) - 16) / 2;

    // Enable TWI
    TWCR = (1 << TWEN);
}


void I2C_Start(uint8_t addr)
{
    // Trimite START
    TWCR = (1 << TWINT) |(1 << TWSTA) | (1 << TWEN);

    // Așteaptă finalizare
    while (!(TWCR & (1 << TWINT)));

    // Verifică status
    if ((TWSR & 0xF8) != START)
        ERROR();
    //incarca slave adress 
    TWDR = addr;
    TWCR = (1<<TWINT) |(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));

    if ((TWSR & 0xF8) != MT_SLA_ACK)
        ERROR();
}
/*
uint8_t i2c_start(void)
{
    TWCR = (1 << TWINT) |
           (1 << TWSTA) |
           (1 << TWEN);

    while (!(TWCR & (1 << TWINT)));

    if ((TWSR & 0xF8) != START)
        return 0;

    return 1;
}

*/


void I2C_Stop(void)
{
    TWCR = (1 << TWINT) |(1 << TWEN)  | (1 << TWSTO);

    // opțional: așteaptă eliberarea magistralei
    while (TWCR & (1 << TWSTO));
}


void I2C_Write(uint8_t data)
{
    // Încarcă datele
    TWDR = data;

    // Pornește transmisia
    TWCR = (1 << TWINT) |(1 << TWEN);

    // Așteaptă terminarea transmisiei
    while (!(TWCR & (1 << TWINT)));

    // Verifică ACK
    if ((TWSR & 0xF8) != MT_DATA_ACK)
        ERROR();
}