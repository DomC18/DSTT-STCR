#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

struct PressureData {
    float pressureBar;
    float temperatureC;
    float depthM;
}

bool initPressureSensor();
bool readSensor(PressureData& pressureData);

#endif