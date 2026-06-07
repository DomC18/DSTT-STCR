#include <SPI.h>
#include <SD.h>
#include <RTClib.h>

#include "sd_logger.h"
#include "gps_manager.h"
#include "config.h"

bool initSDCard() {
  if (!SD.begin(SD_CS)) {
    return false;
  }

  return true;
}

void logData(DateTime now, float batteryVoltage, float pressure, GPSData fix) {
  char filename[20];
  sprintf(filename, "/%04d%02d%02d.csv", now.year(), now.month(), now.day());

  if (!SD.exists(filename)) {
    File newFile = SD.open(filename, FILE_WRITE);
    if (newFile) {
      newFile.println("date,time,batteryVoltage,pressure,latitude,longitude");
      newFile.close();
    }
  }

  char dateString[16];
  char timeString[16];
  sprintf(dateString, "%04d-%02d-%02d", now.year(), now.month(), now.day());
  sprintf(timeString, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());

  File logFile = SD.open(filename, FILE_APPEND);
  if (logFile) {
    logFile.print(dateString);
    logFile.print(",");
    logFile.print(timeString);
    logFile.print(",");
    logFile.print(batteryVoltage);
    logFile.print(",");
    logFile.print(pressure);
    logFile.print(",");
    if (fix.validFix) {
      logFile.print(fix.latitude, 6);
      logFile.print(",");
      logFile.println(fix.longitude, 6);
    } else {
      logFile.print("-----");
      logFile.print(",");
      logFile.println("-----");
    }
    logFile.close();
  }
}