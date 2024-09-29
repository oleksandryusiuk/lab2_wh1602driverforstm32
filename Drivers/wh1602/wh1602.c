/** @file wh1602.c
 *
 * @brief wh1602 driver
 * @date: Sep 21, 2024
 *
 */

#include "wh1602.h"

volatile uint8_t sendCount = 0;

/**
  * @brief wh1602 initialization function
  * according to https://www.sparkfun.com/datasheets/LCD/HD44780.pdf
  * page 46 Figure 24
  *
  * @param None
  * @retval None
  */
void wh1602_Init(void) {
	HAL_Delay(15); 					// wait > 15 ms after power on
	/* 0000 1100 */
	wh1602_SendData(0x0C);  		// still in 8-bit mode...
	HAL_Delay(5); 					// wit > 4.1 ms;
	wh1602_SendData(0x0C);			// still in 8-bit mode...
	HAL_Delay(1); 					// wait > 100 microseconds
	wh1602_SendData(0x0C);			// still in 8-bit mode...

	wh1602_SendData(0x08);  		// now we are in 4-bit mode;

	/* 0000 1000 */					// now when we are in 4-bit mode,
	wh1602_SendData(0x08);			// we are able to set 2 line mode
	/* 0011 0000 */					// and need to specify that we are
	wh1602_SendData(0x30);			// in 4-bit mode again;

	wh1602_CheckBF();

	wh1602_SendData(0x0);			// display ON/OFF control: First nibble;
	/* 00111000 */					//
	wh1602_SendData(0x38);			// Turning on Display and cursor.

	wh1602_CheckBF();

	wh1602_SendData(0x0);			// entry mode set: First nibble;
	/* 0001 1000 */
	wh1602_SendData(0x18);			// sets mode to increment the address
									// by one and shift cursor to the right
									// when writing symbols.

}

/**
  * @brief sending 6-bit data packet to wh1602
  *
  * @param data 6-bit wh1602 instruction
  * @retval None
  */
void wh1602_SendData(uint8_t data)
{
	/****************************************************************************/
	/* | BIT 7 | BIT 6 | BIT 5 |  BIT 4 |  BIT 3 |  BIT 2 | BIT 1   | BIT 0   | */
	/* |  RS   |  RW   | DB7   |  DB6   |  DB5   |  DB4   | IGNORED | IGNORED | */
	/****************************************************************************/
	HAL_GPIO_WritePin(GPIOE, RS_PIN, ((data>>7) & 0x01)); /* 00110000 >> 7 -> 0000 0001 */
	HAL_GPIO_WritePin(GPIOE, RW_PIN, ((data>>6) & 0x01));
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOE, E_PIN, GPIO_PIN_SET);

	HAL_GPIO_WritePin(GPIOE, DB7_PIN, ((data>>5) & 0x01));
	HAL_GPIO_WritePin(GPIOE, DB6_PIN, ((data>>4) & 0x01));
	HAL_GPIO_WritePin(GPIOE, DB5_PIN, ((data>>3) & 0x01));
	HAL_GPIO_WritePin(GPIOE, DB4_PIN, ((data>>2) & 0x01));

	HAL_GPIO_WritePin(GPIOE, E_PIN, GPIO_PIN_RESET);
	HAL_Delay(1);

}


/**
  * @brief function for sending characters to wh1602
  * @param ch character to be printed
  * @retval None
  */

void wh1602_SendChar(char ch)
{
	wh1602_CheckBF();
	// If we fill first row, we need to start printing at second row
	// by setting current Display data ram at 0x40
	if (sendCount == 16)
	{
		// 0x40 = 0b 0100 0000
		wh1602_SendData(0b00110000);
		wh1602_SendData(0b00000000);
		sendCount = 0;
		HAL_Delay(100);
	}
	/* 's' = 0111 0011 >> 2 -> 00 0111 00 & 00 1111 00 -> 00 0111 00 | 10 0000 00 -> 10 0111 00*/
	/* 's' = 0111 0011 << 2 -> 11 0011 00 & 00 1111 00 -> 00 0011 00 | 10 0000 00 -> 10 0011 00*/
	wh1602_SendData(((ch>>2) & 0b00111100) | 0b10000000 );
	wh1602_SendData(((ch<<2) & 0b00111100) | 0b10000000 );
	sendCount++;
}

/**
  * @brief function for checking busy flag
  * @param None
  * @retval None
  */
void wh1602_NullCounter(void)
{
	sendCount = 0;
}
void wh1602_CheckBF(void)
{
	uint32_t try = 1000;	// counter variable to calculate checks
	do
	{
		try--;
		wh1602_SendData(0b01000000);
		wh1602_SendData(0b01000000);
		HAL_Delay(1);

	}
	while (HAL_GPIO_ReadPin(GPIOE, DB7_PIN) || (try > 1000));	// exit whether we are no longer busy (BF = 0) or we have made 1000+ checks
}

/**
  * @brief wh1602 cleaning screen function
  *
  * @param None
  * @retval None
  *
  */
void wh1602_Clear(void)
{
	wh1602_CheckBF();
	wh1602_SendData(0x0);
	wh1602_SendData(0x04);
	sendCount = 0;
}







