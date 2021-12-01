#include "watchdog.hpp"
#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(D12, OUTPUT);
  pinMode(USER_BTN, INPUT);
  watchdogInit(5);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(!digitalRead(USER_BTN)) {
    watchdogPet();
  }
  
}