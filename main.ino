#include <Arduino.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <esp_sleep.h>
#include "config.h"
#include "pressure_sensor.h"
#include "sd_logger.h"
#include "state_manager.h"
#include "temperature_sensor.h"
#include "timer.h"

PressureData pressureData;

bool initSys() {
    // if (!initSDCard()) {
    //     Serial.println("SD initialization failed.");
    //     return false;
    // }
    if (!initPressureSensor()) {
        Serial.println("Pressure sensor initialization failed.");
        return false;
    }
}

void setup() {
    Serial.begin(BAUD_RATE);
    delay(DEFAULT_DELAY);
    printWakeupReason(); 
    if (!initSys()) {
        Serial.println("Init unsucessful.");
        return;
    }
    
    if (!readPressure(pressureData)) {
        Serial.println("Sensor read failed.");
        while (true) {
            delay(DEFAULT_DELAY);
        }
    }
    printPressureData(pressureData);
    
    // if (!logData(pressureData)) {
    //     Serial.println("Logging failed.");
    // }
    // updateState(pressureData);

    // Serial.println("Cycle complete.");
    // setWakeTimer(isSurfaced());
    // delay(DEFAULT_DELAY);
    // esp_deep_sleep_start();
}

void loop() {
    if (!readPressure(pressureData)) {
        Serial.println("Sensor read failed.");
        while (true) {
            delay(DEFAULT_DELAY);
        }
    }
    printPressureData(pressureData);
}
