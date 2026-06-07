#ifndef SD_LOGGER_H
#define SD_LOGGER_H

#include <RTClib.h>
#include "gps_manager.h"

bool initSDCard();
void logData(DateTime now, float batteryVoltage, float pressure, GPSData fix);

#endif