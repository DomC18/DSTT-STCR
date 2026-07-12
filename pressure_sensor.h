#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

#include <cstdint>

struct PressureData {
    float pressureBar;
    float temperatureC;
    float depthM;
};

bool readMemoryFloat(uint8_t address, float &value);
bool readCalibration();
bool initPressureSensor();
float calculateDepth(PressureData &pressureData);
bool readSensor(PressureData &pressureData);
void printPressureData(PressureData &pressureData);

#endif
