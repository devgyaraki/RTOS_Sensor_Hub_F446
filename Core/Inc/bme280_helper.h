/*
 * bme280_helper.h
 *
 *  Created on: Jul 6, 2026
 *      Author: Roland
 */

#ifndef INC_BME280_HELPER_H_
#define INC_BME280_HELPER_H_

#include "bme280.h"
#include "main.h"

int8_t bme280_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);
int8_t bme280_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr);
void bme280_delay_us(uint32_t period, void *intf_ptr);

#endif /* INC_BME280_HELPER_H_ */
