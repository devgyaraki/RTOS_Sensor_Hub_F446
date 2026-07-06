/*
 * rtc_helper.c
 *
 *  Created on: Jul 6, 2026
 *      Author: Roland
 */

#include "rtc_helper.h"
#include "main.h"
extern I2C_HandleTypeDef hi2c1;

uint8_t DS3231_GetHours(void) {
    uint8_t data;
    HAL_I2C_Mem_Read(&hi2c1, 0xD0, 0x02, 1, &data, 1, 100);
    return ((data >> 4) * 10) + (data & 0x0F);
}

uint8_t DS3231_GetMinutes(void) {
    uint8_t data;
    HAL_I2C_Mem_Read(&hi2c1, 0xD0, 0x01, 1, &data, 1, 100);
    return ((data >> 4) * 10) + (data & 0x0F);
}

uint8_t DS3231_GetSeconds(void) {
    uint8_t data;
    HAL_I2C_Mem_Read(&hi2c1, 0xD0, 0x00, 1, &data, 1, 100);
    return ((data >> 4) * 10) + (data & 0x0F);
}

void DS3231_Init(I2C_HandleTypeDef *hi2c) {

}

#define DS3231_ADDR (0x68 << 1)

void DS3231_SetDate(uint8_t day, uint8_t month, uint8_t year)
{
    uint8_t data[3];

    data[0] = ((day / 10) << 4) | (day % 10);
    data[1] = (((month / 10) & 0x01) << 4) | (month % 10);   // Century = 0
    data[2] = ((year / 10) << 4) | (year % 10);

    HAL_I2C_Mem_Write(&hi2c1,
                      DS3231_ADDR,
                      0x04,
                      I2C_MEMADD_SIZE_8BIT,
                      data,
                      3,
                      HAL_MAX_DELAY);
}

#define DS3231_ADDR (0x68 << 1)    // 0xD0

void DS3231_GetDate(uint8_t *day, uint8_t *month, uint8_t *year)
{
    uint8_t buffer[3];

    if (HAL_I2C_Mem_Read(&hi2c1,
                         DS3231_ADDR,
                         0x04,
                         I2C_MEMADD_SIZE_8BIT,
                         buffer,
                         3,
                         HAL_MAX_DELAY) == HAL_OK)
    {
        // Date (04h)
        *day = (((buffer[0] >> 4) & 0x03) * 10) + (buffer[0] & 0x0F);

        // Month (05h) - Century bit figyelmen kívül hagyva
        *month = (((buffer[1] >> 4) & 0x01) * 10) + (buffer[1] & 0x0F);

        // Year (06h)
        *year = (((buffer[2] >> 4) & 0x0F) * 10) + (buffer[2] & 0x0F);
    }
}
