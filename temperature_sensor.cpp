#include "temperature_sensor.h"
#include "config.h"

#include <OneWireNg_CurrentPlatform.h>
#include <DallasTemperature.h>

static OneWireNg_CurrentPlatform oneWire(DS18B20_PIN);
static DallasTemperature sensors(&oneWire);

bool initTemperatureSensor() {
    sensors.begin();

    if (sensors.getDeviceCount() == 0) {
        Serial.println("No DS18B20 detected.");
        return false;
    }

    sensors.setResolution(12);
    Serial.print("Found ");
    Serial.print(sensors.getDeviceCount());
    Serial.println(" DS18B20 sensor(s).");

    return true;
}

bool readTemperature(float &temperatureC) {
    sensors.requestTemperatures();
    temperatureC = sensors.getTempCByIndex(0);

    if (temperatureC == DEVICE_DISCONNECTED_C) {
        Serial.println("Temperature sensor disconnected.");
        return false;
    }

    return true;
}