#include <Arduino.h>
#include "watchdog.hpp"
#include "stm32l4xx_hal_rcc.h"
#include "stm32lowpower.h"

WatchDog watchdog;
#define LED_PIN D3
#define BUTTON_PIN USER_BTN


void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  if(__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST)) {
    digitalWrite(LED_PIN, HIGH);
  }
  else {
    digitalWrite(LED_PIN, LOW);
  }
  __HAL_RCC_CLEAR_RESET_FLAGS();
  watchdog.init(10);
  LowPower.begin();
}

void loop() {
  while(!digitalRead(BUTTON_PIN)) {
    watchdog.pet();
  }
  while(1) {
    digitalWrite(LED_PIN, HIGH);
    delay(300);
    digitalWrite(LED_PIN, LOW);
    delay(300);
    digitalWrite(LED_PIN, HIGH);
    delay(300);
    digitalWrite(LED_PIN, LOW);
    watchdog.enableFreezeForShutdown();
    LowPower.shutdown(30000);
  }
}