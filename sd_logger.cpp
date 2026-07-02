#include "sd_logger.h"
#include "config.h"

#include <SPI.h>

static uint32_t sampleNumber = 0;

bool initSDCard() {
    if (!SD.begin(SD_CS)) {
        Serial.println("SD initialization failed.");
        return false;
    }
    Serial.println("SD initialized.");

    return true;
}

bool logData(const PressureData &pressureData) {
    const char *filename = "/log.csv";

    if (!SD.exists(filename)) {
        File file = SD.open(filename, FILE_WRITE);
        if (!file) {
            Serial.println("Failed to create log file.");
            return false;
        }
        file.println("Sample,Elapsed_Time_s,Pressure_bar,Temperature_C,Depth_m");
        file.close();
    }
    File file = SD.open(filename, FILE_APPEND);
    if (!file) {
        Serial.println("Failed to open log file.");
        return false;
    }

    sampleNumber++;
    uint32_t elapsedTime = (sampleNumber - 1) * LOG_INTERVAL_SECONDS;
    file.print(sampleNumber);
    file.print(",");
    file.print(elapsedTime);
    file.print(",");
    file.print(pressureData.pressureBar, 3);
    file.print(",");
    file.print(pressureData.temperatureC, 2);
    file.print(",");
    file.println(pressureData.depthM, 3);
    file.close();
    Serial.println("Data logged.");

    return true;
}