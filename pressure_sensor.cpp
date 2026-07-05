#include "pressure_sensor.h"
#include "config.h"

#include <Wire.h>

static float pressureMin = 0.0f;
static float pressureMax = 10.0f;

static bool readMemoryFloat(uint8_t address, float &value) {
    Wire.beginTransmission(PRESSURE_ADDRESS);
    Wire.write(0x69);
    Wire.write(address);

    if (Wire.endTransmission(false) != 0) return false;
    if (Wire.requestFrom(PRESSURE_ADDRESS, (uint8_t)4) != 4) return false;

    union {
        uint8_t bytes[4];
        float number;
    } data;

    data.bytes[3] = Wire.read();
    data.bytes[2] = Wire.read();
    data.bytes[1] = Wire.read();
    data.bytes[0] = Wire.read();

    value = data.number;

    return true;
}

static bool readCalibration() {
    if (!readMemoryFloat(0x13, pressureMin)) return false;
    if (!readMemoryFloat(0x15, pressureMax)) return false;

    return true;
}

static float calculateDepth(float pressureBar) {
    float pressurePa = (pressureBar - ATM_PRESSURE_BAR) * 100000.0f;
    if (pressurePa < 0) pressurePa = 0;

    return pressurePa / (WATER_DENSITY * GRAVITY);
}



bool initPressureSensor() {
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

    if (!readCalibration()) {
        Serial.println("Failed to read Pressure calibration.");
        return false;
    }

    Serial.println("Pressure sensor initialized.");
    Serial.print("Pressure Range: ");
    Serial.print(pressureMin);
    Serial.print(" to ");
    Serial.print(pressureMax);
    Serial.println(" bar");

    return true;
}

bool readPressureData(PressureData &pressureData) {
    Wire.beginTransmission(PRESSURE_ADDRESS);
    Wire.write(0xAC);

    if (Wire.endTransmission() != 0) return false;
    delay(8);
    if (Wire.requestFrom(PRESSURE_ADDRESS, (uint8_t)5) != 5) return false;

    uint8_t status = Wire.read();
    uint16_t pressureRaw = (Wire.read() << 8) | Wire.read();
    uint16_t temperatureRaw = (Wire.read() << 8) | Wire.read();

    if (status != 0) {
        Serial.println("Pressure conversion failed.");
        return false;
    }

    pressureData.pressureBar = ((float)pressureRaw - 16384.0f) * (pressureMax - pressureMin) / 32768.0f + pressureMin;
    pressureData.temperatureC = ((((float)(temperatureRaw >> 4)) - 24.0f) * 0.05f) - 50.0f;
    pressureData.depthM = calculateDepth(pressureData.pressureBar);

    return true;
}