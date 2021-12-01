#pragma once
#include <stm32l1xx.h>
#include <stm32l1xx_hal_iwdg.h>
#include <stm32l1xx_hal_wwdg.h>
#include "constants.hpp"

IWDG_HandleTypeDef IwdgHandle;

void watchdogInit(uint32_t secondsToTimeout) {
  //Assuming LSI runs on 32kHz and we want the 
	//max watchdog value, we use the highest prescaler of 
	//256 to get 32000 Hz / 256 = 125 Hz (watchdog clock pulses per second)
	//we use the maximum reload value of 0x0FFF = 4095. 
	//meaning that the watchdog has a max timeout of 4095 / 125 = 32.76 seconds. 
	//If HAL_IWDG_Refresh() is not called before this timeout expires, the micro-
	//controller resets.
  IwdgHandle.Instance = IWDG;
	IwdgHandle.Init.Prescaler = IWDG_PRESCALER_256;
	IwdgHandle.Init.Reload    = secondsToTimeout * kWatchdogPulsesPerSecond;

	if(HAL_IWDG_Init(&IwdgHandle) != HAL_OK)
	{
		/* Initialization Error */
	}
}

void watchdogPet() {
  HAL_IWDG_Refresh(&IwdgHandle);
}