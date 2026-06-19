#include <test.h>
#include <config.h>
#include <rtc_manager.h>
#include <sd_logger.h>
#include <power_manager.h>
#include <battery_monitor.h>
#include <pressure_sensor.h>
#include <gps_manager.h>

void setup() {
    Serial.begin(19200);
    delay(1000);
    
    Serial.println("Entering deep sleep...");
    enterDeepSleep();
    Serial.println("Out of deep sleep.");
    float voltage = batteryVoltage();
    float pressure = readPressurePSI();
    GPSData fix = getGPSFix(1000);
    DateTime now = DateTime(2026, 6, 3, 23, 0, 0);
    logData(now, voltage, pressure, fix);
}

void loop() {
    
}