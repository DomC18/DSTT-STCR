#include <Arduino.h>
#include "battery_manager.h"

uint16_t readMillivolts(uint8_t pin, bool isBattery) {
    uint32_t sum = 0;
    uint32_t read;

    for (int i = 0; i < 8; i++) {
        read = analogReadMilliVolts(pin);
        sum += read;
        delay(5);
    }

    float adcVoltage = sum / (float)8;
    float battVoltage = adcVoltage;
    if (isBattery) battVoltage *= 1.37f;

    Serial.print("Voltage on pin "); Serial.print(pin); Serial.print(": ");
    Serial.println(battVoltage);

    return (uint16_t)constrain(battVoltage, 0.0f, 65535.0f);
}