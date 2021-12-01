#include <Arduino.h>
#include "watchdog.hpp"
#include "stm32l4xx_hal_rcc.h"
#include "stm32lowpower.h"

WatchDog watchdog;

void setup() {
  // put your setup code here, to run once:
  pinMode(D8, OUTPUT);
  if(__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST)) {
    digitalWrite(D8, HIGH);
  }
  else {
    digitalWrite(D8, LOW);
  }
  __HAL_RCC_CLEAR_RESET_FLAGS();
  pinMode(D7, INPUT);
  watchdog.init(10);
  LowPower.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  while(digitalRead(D7)) {
    watchdog.pet();
  }

  while(1) {
    digitalWrite(D8, HIGH);
    delay(300);
    digitalWrite(D8, LOW);
    delay(300);
    LowPower.shutdown(30000);
  }
}