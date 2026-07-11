#include "temperature_sensor.h"
#include "config.h"

#include <DS18B20.h>

static DS18B20 ds(DS18B20_PIN);
static bool sensorFound = false;

bool initTemperatureSensor() {
    Serial.println("Starting DS18B20 test");
    if (ds.selectNext()) {
        Serial.println("Sensor found");
        sensorFound = true;
    }

    return sensorFound;
}

bool readTemperature(float &temperatureC) {
    if (!sensorFound) return false;
    temperatureC = ds.getTempC();

    return true;
}