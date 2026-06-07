#ifndef GPS_MANAGER_H
#define GPS_MANAGER_H

#include <cstdint>

struct GPSData {
  bool validFix;
  double latitude;
  double longitude;
};

bool initGPS();
GPSData getGPSFix(uint32_t timeoutMs = 120000);

#endif