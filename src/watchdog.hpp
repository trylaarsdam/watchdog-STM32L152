#pragma once
#include <stm32l1xx.h>
#include <stm32l1xx_hal_iwdg.h>
#include <stm32l1xx_hal_wwdg.h>
#include "constants.hpp"

#define kWatchdogPulsesPerSecond 155 // assuming LSE at 32.768kHz, prescaler = 256, 155 * seconds gives an accurate reload value
IWDG_HandleTypeDef IwdgHandle;

void watchdogInit(uint32_t secondsToTimeout) {
  IwdgHandle.Instance = IWDG;
	IwdgHandle.Init.Prescaler = IWDG_PRESCALER_256;
	IwdgHandle.Init.Reload    = secondsToTimeout * kWatchdogPulsesPerSecond;

	if(HAL_IWDG_Init(&IwdgHandle) != HAL_OK)
	{
		/* Initialization Error */
	}
}

void watchdogPet() {
  HAL_IWDG_Refresh(&IwdgHandle); // resets the IWDG counter back to 0
}