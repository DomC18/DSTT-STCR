#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "config.h"
#include "pressure_sensor.h"
#include "sd_logger.h"
#include "temperature_sensor.h"
#include "timer.h"


void init() {
    if (!initSDCard()) {
        Serial.println("SD initialization failed.");
        while (true) {
            delay(DEFAULT_DELAY);
        }
    }
    // if (!initPressureSensor()) {
    //     Serial.println("Pressure sensor initialization failed.");
    //     while (true) {
    //         delay(DEFAULT_DELAY);
    //     }
    // }
}

void setup() {
    Serial.begin(BAUD_RATE);
    delay(DEFAULT_DELAY);
    printWakeupReason(); 
    init();
    
    // PressureData pressureData;
    // if (!readSensor(pressureData)) {
    //     Serial.println("Sensor read failed.");
    //     while (true) {
    //         delay(DEFAULT_DELAY);
    //     }
    // }
    // printPressureData(pressureData);
    // if (!logData(pressureData)) {
    //     Serial.println("Logging failed.");
    // }
    // updateState(pressureData);

    // Serial.println("Cycle complete.");
    // setWakeTimer(isSurfaced());
    // delay(DEFAULT_DELAY);
    // enterDeepSleep();
}

void loop() {

}
