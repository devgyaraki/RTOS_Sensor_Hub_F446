/*
 * low_power.c
 *
 *  Created on: Jul 6, 2026
 *      Author: Roland
 */

#include "main.h"

volatile uint32_t sleepCounter = 0;

void PreSleepProcessing(uint32_t ulExpectedIdleTime)
{
    (void)ulExpectedIdleTime;

    sleepCounter++;

    HAL_SuspendTick();

    HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON,
                           PWR_SLEEPENTRY_WFI);
}

void PostSleepProcessing(uint32_t ulExpectedIdleTime)
{
    (void)ulExpectedIdleTime;

    HAL_ResumeTick();
}
