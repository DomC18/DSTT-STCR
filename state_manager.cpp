#include <Arduino.h>
#include "state_manager.h"
#include "config.h"
#include "pressure_sensor.h"

void updateState(TagState currentState, const PressureData& pressureData, uint32_t &dryCount, uint32_t &surfacedSamples) {
    if (pressureData.pressureBar < DRY_BASELINE) {
        surfacedSamples++;
        if (surfacedSamples >= 5) {
            currentState = SURFACED;
            dryCount++;
        }
    } else {
        surfacedSamples = 0;
        dryCount = 0;
        currentState = SUBMERGED;
    }
}