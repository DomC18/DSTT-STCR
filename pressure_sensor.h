#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

#include <cstdint>

struct PressureData {
    float pressureRaw;
    float pressureBar;
    float temperatureRaw;
    float temperatureC;
    float depthM;
    bool submerged;
};

bool readMemoryWord(uint8_t address, uint16_t &value);
bool readMemoryFloat(uint8_t addressMSB, float &value);
bool readCalibration();
bool initPressureSensor();
float calculateDepth(PressureData &pressureData);
bool readPressure(PressureData &pressureData);
void printPressureData(PressureData &pressureData);

#endif
