#include <Arduino.h>
#include <DS18B20.h>
#include "temperature_sensor.h"
#include "config.h"

static DS18B20 ds(DS18B20_PIN);
static bool sensorFound = false;

bool initTemperatureSensor() {
    if (!ds.selectNext()) {
        return false;
    }
    sensorFound = true;
    
    return true;
}

bool readTemperature(float &temperatureC) {
    if (!sensorFound) return false;
    temperatureC = ds.getTempC();

    return true;
}
