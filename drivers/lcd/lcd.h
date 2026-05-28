#ifndef LCD_I2C_H_
#define LCD_I2C_H_

#include <stdint.h>
#include <avr/io.h>

void LCD_Init(void);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_Print(char *str);
void LCD_Command(uint8_t cmd);
void LCD_Data(uint8_t data);

#endif