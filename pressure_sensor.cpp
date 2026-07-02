#include "pressure_sensor.h"
#include "config.h"

#include <Wire.h>

bool initPressureSensor() {
    Wire.beginTransmission(KELLER_I2C_ADDRESS);
    if (Wire.endTransmission() != 0) {
        Serial.println("Keller sensor not detected.");
        return false;
    }
    Serial.println("Keller sensor initialized.");

    return true;
}

bool readSensor(PressureData &pressureData) {
    // Replace this section with Keller I2C commands.
    pressureData.pressureBar = 1.01325f;
    pressureData.temperatureC = 24.5f;
    pressureData.depthM = calculateDepth(pressureData.pressureBar);

    return true;
}

float calculateDepth(float pressureBar) {
    float depth = ((pressureBar - ATM_PRESSURE_BAR) * 100000.0f) / (WATER_DENSITY * GRAVITY);
    if (depth < 0.0f) depth = 0.0f;
    
    return depth;
}