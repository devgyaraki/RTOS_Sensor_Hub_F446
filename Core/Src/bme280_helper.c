/*
 * bme280_helper.c
 *
 *  Created on: Jul 6, 2026
 *      Author: Roland
 */

#include "bme280.h"
#include "main.h"

extern I2C_HandleTypeDef hi2c1;

int8_t bme280_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr) {
    // Ha a HAL olvasás nem HAL_OK (pl. timeout-ra futott vagy hibázott),
    // akkor adjunk vissza hibakódot (pl. -1), különben 0-t (BME280_OK)!
    if (HAL_I2C_Mem_Read(&hi2c1, 0xEC, reg_addr, 1, reg_data, len, 100) != HAL_OK) {
        return -1; // BME280_E_COMM_FAIL vagy bármilyen negatív hibaérték
    }
    return BME280_OK; // azaz 0
}

int8_t bme280_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr) {
    if (HAL_I2C_Mem_Write(&hi2c1, 0xEC, reg_addr, 1, (uint8_t*)reg_data, len, 100) != HAL_OK) {
        return -1;
    }
    return BME280_OK;
}

void bme280_delay_us(uint32_t period, void *intf_ptr) {
    HAL_Delay(period / 1000 + 1);
}
