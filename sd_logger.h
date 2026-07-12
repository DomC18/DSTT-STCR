#ifndef SD_LOGGER_H
#define SD_LOGGER_H

#include "pressure_sensor.h"

bool initSDCard();
bool logData(const PressureData& pressureData);

#endif
