/*
 * rtc_helper.c
 *
 *  Created on: Jul 6, 2026
 *      Author: Roland
 */

#include "rtc_helper.h"
#include "main.h"
#include <stdbool.h>

extern I2C_HandleTypeDef hi2c1;

#define DS3231_ADDR (0x68 << 1)    // 0xD0
#define RTC_TIMEOUT 50             // 50 ms timeout

// I2C periféria szoftveres resetelése, ha letapadna
void DS3231_ResetI2C(void) {
    HAL_I2C_DeInit(&hi2c1);
    // Kicsi várakozás a GPIO/periféria rendeződésére
    for(volatile int i = 0; i < 1000; i++);
    HAL_I2C_Init(&hi2c1);
}

uint8_t DS3231_GetHours(void) {
    uint8_t data = 0;
    if (HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDR, 0x02, 1, &data, 1, RTC_TIMEOUT) != HAL_OK) {
        DS3231_ResetI2C(); // Ha hiba van, reseteljük az I2C-t, hogy ne tapadjon le
        return 0;
    }
    return ((data >> 4) * 10) + (data & 0x0F);
}

uint8_t DS3231_GetMinutes(void) {
    uint8_t data = 0;
    if (HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDR, 0x01, 1, &data, 1, RTC_TIMEOUT) != HAL_OK) {
        DS3231_ResetI2C();
        return 0;
    }
    return ((data >> 4) * 10) + (data & 0x0F);
}

uint8_t DS3231_GetSeconds(void) {
    uint8_t data = 0;
    if (HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDR, 0x00, 1, &data, 1, RTC_TIMEOUT) != HAL_OK) {
        DS3231_ResetI2C();
        return 0;
    }
    return ((data >> 4) * 10) + (data & 0x0F);
}

void DS3231_Init(I2C_HandleTypeDef *hi2c) {
    // Kezdeti beállítások ha szükséges
}

HAL_StatusTypeDef DS3231_SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
    uint8_t data[3];
    data[0] = ((seconds / 10) << 4) | (seconds % 10);
    data[1] = ((minutes / 10) << 4) | (minutes % 10);
    data[2] = ((hours / 10) << 4) | (hours % 10);

    HAL_StatusTypeDef status = HAL_I2C_Mem_Write(&hi2c1, DS3231_ADDR, 0x00, I2C_MEMADD_SIZE_8BIT, data, 3, RTC_TIMEOUT);
    if (status != HAL_OK) {
        DS3231_ResetI2C();
    }
    return status;
}

bool DS3231_GetTime(uint8_t *hours, uint8_t *minutes, uint8_t *seconds)
{
    uint8_t buffer[3];

    // A DS3231-ben a 0x00 a Seconds, 0x01 a Minutes, 0x02 a Hours (egymás mellett vannak!)
    if (HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDR, 0x00, I2C_MEMADD_SIZE_8BIT, buffer, 3, RTC_TIMEOUT) == HAL_OK)
    {
        *seconds = (((buffer[0] >> 4) & 0x07) * 10) + (buffer[0] & 0x0F);
        *minutes = (((buffer[1] >> 4) & 0x07) * 10) + (buffer[1] & 0x0F);
        *hours   = (((buffer[2] >> 4) & 0x03) * 10) + (buffer[2] & 0x0F);
        return true;
    }

    DS3231_ResetI2C(); // Hiba esetén I2C periféria újraindítása
    return false;
}

HAL_StatusTypeDef DS3231_SetDate(uint8_t day, uint8_t month, uint8_t year)
{
    uint8_t data[3];
    data[0] = ((day / 10) << 4) | (day % 10);
    data[1] = (((month / 10) & 0x01) << 4) | (month % 10);
    data[2] = ((year / 10) << 4) | (year % 10);

    HAL_StatusTypeDef status = HAL_I2C_Mem_Write(&hi2c1, DS3231_ADDR, 0x04, I2C_MEMADD_SIZE_8BIT, data, 3, RTC_TIMEOUT);
    if (status != HAL_OK) {
        DS3231_ResetI2C();
    }
    return status;
}

bool DS3231_GetDate(uint8_t *day, uint8_t *month, uint8_t *year)
{
    uint8_t buffer[3];

    if (HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDR, 0x04, I2C_MEMADD_SIZE_8BIT, buffer, 3, RTC_TIMEOUT) == HAL_OK)
    {
        *day   = (((buffer[0] >> 4) & 0x03) * 10) + (buffer[0] & 0x0F);
        *month = (((buffer[1] >> 4) & 0x01) * 10) + (buffer[1] & 0x0F);
        *year  = (((buffer[2] >> 4) & 0x0F) * 10) + (buffer[2] & 0x0F);
        return true;
    }

    DS3231_ResetI2C(); // Hiba esetén I2C periféria újraindítása
    return false;
}
