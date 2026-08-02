#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "sd_logger.h"
#include "config.h"

bool initSDCard() {
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, SD_CS); // Initialize SPI with SCK, MISO, MOSI, and CS pins
    if (!SD.begin(SD_CS)) {
        return false;
    }

    return true;
}

bool logData(const PressureData &pressureData, const char* filename, uint32_t &sampleNumber, uint32_t &elapsedTimeSeconds) {
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
    file.print(sampleNumber);
    file.print(",");
    file.print(elapsedTimeSeconds);
    file.print(",");
    file.print(pressureData.pressureBar, 3);
    file.print(",");
    file.print(pressureData.temperatureC, 2);
    file.print(",");
    file.print(pressureData.depthM, 3);
    file.print(",");

    file.println();
    file.close();
    Serial.println("Data logged.");

    return true;
}

bool readData(const char* filename) {
    File file = SD.open(filename);
    if (file) {
        Serial.print(filename); 
        Serial.println(": ");
        while (file.available()) {
        char c = file.read();
        Serial.write(c);
        }
        file.close();
    } else {
        Serial.print("error opening "); 
        Serial.println(filename);
        return false;
    }

    return true;
}
