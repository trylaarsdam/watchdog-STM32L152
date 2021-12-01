#include "watchdog.hpp"


void WatchDog::init(uint32_t secondsToTimeout) {
  watchdogEnabled = true;
  IwdgHandle.Instance = IWDG;
	IwdgHandle.Init.Prescaler = IWDG_PRESCALER_256;
	IwdgHandle.Init.Reload    = secondsToTimeout * kWatchdogPulsesPerSecond;

	if(HAL_IWDG_Init(&IwdgHandle) != HAL_OK)
	{
		/* Initialization Error */
	}
}

void WatchDog::pet() {
  HAL_IWDG_Refresh(&IwdgHandle); // resets the IWDG counter back to 0
}

bool WatchDog::isEnabled() {
  return watchdogEnabled;
  
  HAL_FLASH_Unlock();
  HAL_FLASH_OB_Unlock();
  SET_BIT(FLASH->OPTR, FLASH_OPTR_nBOOT1_Msk); 
  HAL_FLASH_OB_Lock();
  HAL_FLASH_Lock();
}