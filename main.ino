#include <Wire.h>
#include <SPI.h>

#include "config.h"
#include "power_manager.h"
#include "pressure_sensor.h"
#include "sd_logger.h"
#include "timer.h"

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("=================================");
    Serial.println("Sea Turtle Data Logger - Phase 1");
    Serial.println("=================================");
    // initLowPowerMode();
    // printWakeupReason(); 

    // Wire.begin(I2C_SDA, I2C_SCL);
    // SPI.begin(
    //     SPI_SCK,
    //     SPI_MISO,
    //     SPI_MOSI,
    //     SD_CS
    // );

    // if (!initTemperatureSensor()) {
    //     Serial.println("Temperature sensor initialization failed.");
    //     while (true) {
    //         delay(1000);
    //     }
    // }
    // if (!initSDCard()) {
    //     Serial.println("SD initialization failed.");
    //     while (true) {
    //         delay(1000);
    //     }
    // }
    // if (!initPressureSensor()) {
    //     Serial.println("Pressure sensor initialization failed.");
    //     while (true) {
    //         delay(1000);
    //     }
    // }
    // PressureData pressureData;
    // if (!readSensor(pressureData)) {
    //     Serial.println("Sensor read failed.");
    //     while (true) {
    //         delay(1000);
    //     }
    // }
    // float temperature;
    // if (readTemperature(temperature)) {
    //     Serial.print("Water Temperature: ");
    //     Serial.print(waterTemperature);
    //     Serial.println(" C");
    // }

    // Serial.println();
    // Serial.println("Current Reading");
    // Serial.print("Pressure (bar): ");
    // Serial.println(pressureData.pressureBar, 3);
    // Serial.print("Temperature (C): ");
    // Serial.println(pressureData.temperatureC, 2);
    // Serial.print("Depth (m): ");
    // Serial.println(pressureData.depthM, 3);

    // if (!logData(currentTime, pressureData)) {
    //     Serial.println("Logging failed.");
    // }

    setWakeTimer(LOG_INTERVAL_SECONDS);
    Serial.println("Cycle complete.");
    delay(1000);
    enterDeepSleep();
}

void loop() {}