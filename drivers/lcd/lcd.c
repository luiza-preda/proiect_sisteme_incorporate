#include "lcd.h"
#include "drivers/i2c/i2c.h"

#include "utils/delay.h"

#define LCD_ADDR  0x4E
// 0x27 << 1 = 0x4E

#define LCD_BACKLIGHT 0x08
#define ENABLE        0x04
#define RW             0x00
#define RS             0x01

static void LCD_Write4Bits(uint8_t data);
static void LCD_ExpanderWrite(uint8_t data);
static void LCD_PulseEnable(uint8_t data);

void LCD_ExpanderWrite(uint8_t data)
{
    I2C_Start(LCD_ADDR);
    I2C_Write(data | LCD_BACKLIGHT);
    I2C_Stop();
}

void LCD_PulseEnable(uint8_t data)
{
    LCD_ExpanderWrite(data | ENABLE);
    Delay(1);

    LCD_ExpanderWrite(data & ~ENABLE);
    Delay(50);
}

void LCD_Write4Bits(uint8_t data)
{
    LCD_ExpanderWrite(data);
    LCD_PulseEnable(data);
}

void LCD_Command(uint8_t cmd)
{
    uint8_t high = cmd & 0xF0;
    uint8_t low  = (cmd << 4) & 0xF0;

    LCD_Write4Bits(high | RW);
    LCD_Write4Bits(low  | RW);
}

void LCD_Data(uint8_t data)
{
    uint8_t high = data & 0xF0;
    uint8_t low  = (data << 4) & 0xF0;

    LCD_Write4Bits(high | RS);
    LCD_Write4Bits(low  | RS);
}

void LCD_Init(void)
{
    Delay(50);

    LCD_Write4Bits(0x30);
    Delay(5);

    LCD_Write4Bits(0x30);
    Delay(150);

    LCD_Write4Bits(0x30);
    LCD_Write4Bits(0x20);

    LCD_Command(0x28);
    // 4-bit mode, 2 lines

    LCD_Command(0x08);
    // display OFF

    LCD_Command(0x01);
    // clear

    Delay(2);

    LCD_Command(0x06);
    // entry mode

    LCD_Command(0x0C);
    // display ON
}

void LCD_Clear(void)
{
    LCD_Command(0x01);
   Delay(2);
}

void LCD_SetCursor(uint8_t row, uint8_t col)
{
    uint8_t addr;

    switch(row)
    {
        case 0:
            addr = 0x80 + col;
            break;

        case 1:
            addr = 0xC0 + col;
            break;

        default:
            addr = 0x80 + col;
    }

    LCD_Command(addr);
}

void LCD_Print(char *str)
{
    while(*str)
    {
        LCD_Data(*str++);
    }
}