#include "watchdog.hpp"
#include <Arduino.h>
#include "stm32l1xx_hal_rcc.h"

void setup() {
  // put your setup code here, to run once:
  pinMode(D12, OUTPUT);
  if(__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST)) {
    digitalWrite(D12, HIGH);
  }
  else {
    digitalWrite(D12, LOW);
  }
  pinMode(USER_BTN, INPUT);
  watchdogInit(5);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(!digitalRead(USER_BTN)) {
    watchdogPet();
  }

  while(1) {

  }
}