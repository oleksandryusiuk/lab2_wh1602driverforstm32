/** @file LCD.c
 *
 * @brief LCD library
 *
 * @date: Sep 21, 2024
 *
 */

#include "LCD.h"

/**
 * @brief LCD initialization
 *
 */
void LCD_Init(void)
{
    wh1602_Init();
}

/**
 * @brief Show character on the display
 *
 * @param ch character to display
 */
void LCD_SendChar(char ch)
{
    wh1602_SendChar(ch);
}

/**
 * @brief Show an array of characters on the display
 *
 * @param str string to display
 * @param size number of characters
 */
void LCD_SendString(char *str, uint8_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        wh1602_SendChar(str[i]);
    }
}

/**
 * @brief Clear the LCD
 *
 */
void LCD_Clear(void)
{
    wh1602_Clear();
}

