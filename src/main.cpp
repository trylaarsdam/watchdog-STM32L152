#include <Arduino.h>
#include "watchdog.hpp"
#include "stm32l4xx_hal_rcc.h"
#include "stm32lowpower.h"

IWDG_HandleTypeDef IwdgHandle;
// WatchDog watchdog;

void setup() {
  // put your setup code here, to run once:
  pinMode(D4, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D6, INPUT);
  if(__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST)) {
    digitalWrite(D3, HIGH);
  }
  else {
    digitalWrite(D3, LOW);
  }
  __HAL_RCC_CLEAR_RESET_FLAGS();
  IwdgHandle.Instance = IWDG;
	IwdgHandle.Init.Prescaler = IWDG_PRESCALER_256;
	IwdgHandle.Init.Reload    = 30 * kWatchdogPulsesPerSecond;
  HAL_IWDG_Init(&IwdgHandle);
  // watchdog.init(10);
  // LowPower.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  // digitalWrite(D4, HIGH);
  if(HAL_IWDG_Refresh(&IwdgHandle) != HAL_OK) {
    digitalWrite(D3, HIGH);
    delay(300);
    digitalWrite(D3, LOW);
    delay(3000);
    // delay(100);
  }

  while(1) {
    HAL_IWDG_Refresh(&IwdgHandle);
    //LowPower.shutdown(30000);
  }
}