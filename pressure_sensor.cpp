#include <SPI.h>
#include <Protocentral_ADS1220.h>

#include "pressure_sensor.h"
#include "config.h"

Protocentral_ADS1220 ads1220;

float voltageToPressure(float voltage) {
    if (voltage < SENSOR_MIN_V) {
        voltage = SENSOR_MIN_V;
    }
    if (voltage > SENSOR_MAX_V) {
        voltage = SENSOR_MAX_V;
    }
    float pressure = (voltage - SENSOR_MIN_V) * SENSOR_MAX_PSI / (SENSOR_MAX_V - SENSOR_MIN_V);

    return pressure;
}

bool initPressureSensor() {
    ads1220.begin(ADS1220_CS, ADS1220_DRDY);

    return true;
}

float readPressurePSI() {
    // long rawData = ads1220.Read_SingleShot_WaitForData();
    // float voltage = ((float)rawData / 8388607.0f) * ADC_REFERENCE;
    // float pressure = voltageToPressure(voltage);

    // return pressure;
    return 14.7;
}