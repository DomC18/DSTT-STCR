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
int iteration = 0;

bool initSys() {
    if (!initPressureSensor()) {
        Serial.println("Pressure sensor initialization failed.");
        return false;
    }
    return true;
}

void setup() {
    Serial.begin(BAUD_RATE);
    delay(DEFAULT_DELAY);
    printWakeupReason(); 
    if (!initSys()) {
        Serial.println("Init unsuccessful.");
        Serial.println();
        while (true) {
            delay(DEFAULT_DELAY);
        }
    }
    
    if (!readPressure(pressureData)) {
        Serial.println("Sensor read failed.");
        Serial.println();
        while (true) {
            delay(DEFAULT_DELAY);
        }
    }
    printPressureData(pressureData);
}

void loop() {
    if (iteration <= 100) {
        if (!readPressure(pressureData)) {
            Serial.println("Sensor read failed.");
            while (true) {
                delay(DEFAULT_DELAY);
            }
        }
        printPressureData(pressureData);
    } else {
        if (iteration == 101) {
            Serial.println("sensor done reading");
            for (int i = 0; i < 5; i++) {
                Serial.println();
            }
        }
    }
    iteration++;
}




// #include <Wire.h>
// #include "config.h"

// void setup() {
//     Serial.begin(BAUD_RATE);
//     delay(DEFAULT_DELAY);

//     Wire.begin(I2C_SDA, I2C_SCL);
//     Wire.setClock(50000);

//     Serial.println("Scanning...");
//     for (uint8_t addr = 1; addr < 127; addr++) {
//         Wire.beginTransmission(addr);
//         uint8_t end = Wire.endTransmission();
//         Serial.printf("0x%02X -> %d\n", addr, end);
//     }
//     Serial.println("done");
// }

// void loop() {}


// #include <Arduino.h>
// #include <Wire.h>
// #include "config.h"

// void setup() {
//     Serial.begin(19200);
//     delay(1000);

//     pinMode(I2C_SDA, INPUT_PULLUP);
//     pinMode(I2C_SCL, INPUT_PULLUP);

//     Serial.printf("SDA = %d\n", digitalRead(I2C_SDA));
//     Serial.printf("SCL = %d\n", digitalRead(I2C_SCL));
// }

// void loop() {}