/*
 * rtc_helper.h
 *
 *  Created on: Jul 6, 2026
 *      Author: Roland
 */

#ifndef INC_RTC_HELPER_H_
#define INC_RTC_HELPER_H_

#include "main.h"
void DS3231_Init(I2C_HandleTypeDef *hi2c);
uint8_t DS3231_GetHours(void);
uint8_t DS3231_GetMinutes(void);
uint8_t DS3231_GetSeconds(void);

#endif /* INC_RTC_HELPER_H_ */
