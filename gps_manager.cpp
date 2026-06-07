#include "gps_manager.h"

#include <TinyGPS++.h>

TinyGPSPlus gps;
HardwareSerial GPSSerial(1);

bool initGPS() {
  GPSSerial.begin(9600, SERIAL_8N1, 20, 21); //RX, TX
  return true;
}

GPSData getGPSFix(uint32_t timeoutMs) {
  GPSData fix;
  fix.validFix = true;
  fix.latitude = 0;
  fix.longitude = 0;

  // uint32_t startTime = millis();
  // while ((millis() - startTime) < timeoutMs) {
  //   while (GPSSerial.available()) {
  //     gps.encode(GPSSerial.read());
  //   }

  //   if (gps.location.isValid() && gps.location.isUpdated()) {
  //     fix.validFix = true;
  //     fix.latitude = gps.location.lat();
  //     fix.longitude = gps.location.lng();

  //     return fix;
  //   }
  // }

  return fix;
}