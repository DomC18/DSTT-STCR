#include <Arduino.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <esp_sleep.h>
#include "battery_manager.h"
#include "config.h"
#include "pressure_sensor.h"
#include "sd_logger.h"
#include "state_manager.h"
#include "timer.h"

const char* fileName = "/log16.csv";
PressureData pressureData;
TagState currentState;
uint32_t dryCount = 0;
uint32_t surfacedSamples = 0;
RTC_DATA_ATTR uint32_t sampleNumber = 0;
RTC_DATA_ATTR uint32_t elapsedTimeSeconds = 0;
int iteration = 0;

bool initSys() {
    if (!initPressureSensor()) {
        Serial.println("Pressure sensor initialization failed.");
        return false;
    }
    if (!initSDCard()) {
        Serial.println("SD card initialization failed.");
        return false;
    }
    return true;
}

void setup() {
    Serial.begin(BAUD_RATE);
    delay(DEFAULT_DELAY);
    printWakeupReason(); 

    readMillivolts(D2, false);
    pinMode(D0, OUTPUT);
    digitalWrite(D0, LOW);
    delay(5000);

    if (!initSys()) {
        Serial.println("Init unsuccessful.");
        Serial.println();
        while (true) {
            delay(DEFAULT_DELAY);
        }
    }
}

void loop() {
    if (iteration <= 50) {
        Serial.print("Iteration: ");
        Serial.println(iteration);
        // if (readMillivolts(D2, false) > 650) {
            // Serial.println("Underwater");
            if (!readPressureSensor(pressureData)) {
                Serial.println("pressure read failed");
                Serial.println();
            } else {
                updateState(currentState, pressureData, dryCount, surfacedSamples);
                printPressureData(pressureData);
                logData(pressureData, fileName);
                Serial.println();
                // elapsedTimeSeconds += 30;
                // setWakeTimer(30);
                // esp_deep_sleep_start();
            }
        // } else {
        //   Serial.println("Above water");
        // }
    } else if (iteration == 51) {
        Serial.println("pressure data completion");
        readData(fileName);
    }
    iteration++;
    delay(2000);
}
