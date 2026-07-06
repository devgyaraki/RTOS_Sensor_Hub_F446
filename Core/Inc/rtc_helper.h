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
uint8_t DS3231_GetDays(void);
uint8_t DS3231_GetMonths(void);
uint8_t DS3231_GetYears(void);
void DS3231_SetDate(uint8_t day, uint8_t month, uint8_t year);
void DS3231_GetDate(uint8_t *day, uint8_t *month, uint8_t *year);

#endif /* INC_RTC_HELPER_H_ */
