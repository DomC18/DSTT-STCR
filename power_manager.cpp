#include "power_manager.h"
#include "config.h"

#include "esp_sleep.h"

void initLowPowerMode() {
    btStop();
    Serial.println("Low-power mode initialized.");
}

void enterDeepSleep() {
    Serial.println("Entering deep sleep...");
    esp_sleep_enable_timer_wakeup((uint64_t)LOG_INTERVAL_SECONDS * 1000000ULL);
    esp_deep_sleep_start();
}