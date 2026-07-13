#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "pressure_sensor.h"

enum TagState {
    SUBMERGED,
    SURFACED
};

bool isSurfaced();
TagState getCurrentState();
void updateState(const PressureData& pressureData);

#endif