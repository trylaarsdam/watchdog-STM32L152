#pragma once
#include <stm32l1xx.h>
#include <stm32l1xx_hal_iwdg.h>
#include <stm32l1xx_hal_wwdg.h>
#include "constants.hpp"

#define kWatchdogPulsesPerSecond 155 // assuming LSE at 32.768kHz, prescaler = 256, 155 * seconds gives an accurate reload value
IWDG_HandleTypeDef IwdgHandle;

class WatchDog {
    private:
        bool watchdogEnabled = false;
    public:
        void init(uint32_t secondsToTimeout);
        void pet();

        bool isEnabled();

        // void runWhileSleeping(bool yes = true);
        // void runWhileAtBreakpoint(bool yes = true);
};
