/** @file wh1602.h
 *
 * @brief wh1602 driver
 *
 * @date: Sep 21, 2024
 *
 */

#ifndef WH1602_WH1602_H_
#define WH1602_WH1602_H_

#include "stm32f4xx_hal.h"

#include "stdint.h"
// Macro for more clear pin names
//
#define RS_PIN GPIO_PIN_7
#define RW_PIN GPIO_PIN_10
#define E_PIN GPIO_PIN_11
#define DB4_PIN GPIO_PIN_12
#define DB5_PIN GPIO_PIN_13
#define DB6_PIN GPIO_PIN_14
#define DB7_PIN GPIO_PIN_15

//extern volatile uint8_t sendCount;

void wh1602_Init(void);
void wh1602_SendData(uint8_t);
void wh1602_SendChar(char ch);
void wh1602_Clear(void);
void wh1602_CheckBF(void);
void wh1602_NullCounter(void);
#endif /* WH1602_WH1602_H_ */
