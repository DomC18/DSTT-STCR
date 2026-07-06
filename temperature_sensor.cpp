#include "temperature_sensor.h"
#include "config.h"

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

static OneWire oneWireIn(DS18B20_IN);
static OneWire oneWireOut(DS18B20_OUT);
static DallasTemperature sensorIn(&oneWireIn);
static DallasTemperature sensorOut(&oneWireOut);

bool initTemperatureSensor() {
    sensorIn.begin();
    sensorOut.begin();

    if (sensors.getDeviceCount() == 0) {
        Serial.println("No DS18B20 detected.");
        return false;
    }

    return true;
}

bool readTemperature(float &temperatureC) {
    sensorIn.requestTemperatures();
    sensorOut.requestTemperatures();
    temperatureC = sensorIn.getTempCByIndex(0);
    temperatureOut = sensorOut.getTempCByIndex(0);

    if (temperatureC == DEVICE_DISCONNECTED_C) {
        Serial.println("Temperature sensor disconnected.");
        return false;
    }

    return true;
}