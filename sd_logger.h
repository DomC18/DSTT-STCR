#ifndef SD_LOGGER_H
#define SD_LOGGER_H

#include "pressure_sensor.h"

bool initSDCard();
bool logData(const PressureData &pressureData, const char* filename, uint32_t &sampleNumber, uint32_t &elapsedTimeSeconds);
bool readData(const char* filename);

#endif
