#include <Arduino.h>
#include "watchdog.hpp"
#include "stm32l1xx_hal_rcc.h"

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
  pinMode(USER_BTN, INPUT);
  watchdog.init(10);
}

void loop() {
  // put your main code here, to run repeatedly:

  while(digitalRead(USER_BTN)) {
    watchdog.pet();
  }

  while(1) {
    digitalWrite(D8, HIGH);
    delay(300);
    digitalWrite(D8, LOW);
    delay(300);
  }
}