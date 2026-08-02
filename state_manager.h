#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "pressure_sensor.h"

enum TagState {
    SUBMERGED,
    SURFACED
};

void updateState(TagState currentState, const PressureData& pressureData, uint32_t &dryCount, uint32_t &surfacedSamples);

#endif