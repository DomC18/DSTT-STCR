#include <Arduino.h>
#include "state_manager.h"
#include "pressure_sensor.h"

RTC_DATA_ATTR TagState currentState = SUBMERGED;
RTC_DATA_ATTR uint32_t dryCount = 0;
RTC_DATA_ATTR float dryBaseline = 1.01325f;
RTC_DATA_ATTR uint32_t surfacedSamples = 0;

bool isSurfaced() {
    return currentState == SURFACED;
}

TagState getCurrentState() {
    return SUBMERGED;
}

void updateState(const PressureData& pressureData) {
    if (pressureData.pressureBar < dryBaseline) {
        surfacedSamples++;
        if (surfacedSamples >= 5) {
            currentState = SURFACED;
            dryCount++;
        }
    } else {
        surfacedSamples = 0;
        currentState = SUBMERGED;
    }
}