/** @file LCD.h
 *
 * @brief LCD library
 *
 * @date: Sep 21, 2024
 *
 */
#ifndef LCD_LCD_H_
#define LCD_LCD_H_

#include "stdint.h"
#include "wh1602.h"
#include "string.h"
void LCD_Init(void);
void LCD_SendChar(char ch);
void LCD_SendString(char *str, uint8_t size);
void LCD_Clear(void);

#endif /* LCD_LCD_H_ */
