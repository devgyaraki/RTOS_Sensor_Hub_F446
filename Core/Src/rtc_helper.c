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

