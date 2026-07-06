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
    HAL_I2C_Mem_Read(&hi2c1, 0xEC, reg_addr, 1, reg_data, len, 100); // 0xEC vagy 0xEE a BME280 címe
    return 0;
}

int8_t bme280_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr) {
    HAL_I2C_Mem_Write(&hi2c1, 0xEC, reg_addr, 1, (uint8_t*)reg_data, len, 100);
    return 0;
}

void bme280_delay_us(uint32_t period, void *intf_ptr) {
    HAL_Delay(period / 1000 + 1);
}
