#include <Arduino.h>
#include <esp_sleep.h>
#include "timer.h"

void enterDeepSleep() {
    esp_deep_sleep_start();
}

void setWakeTimer(bool isSurfaced) {
    uint64_t wakeTimeUS = isSurfaced ? SURFACED_INTERVAL_SEC * UNIX_TIME : SUBMERGED_INTERVAL_SEC * UNIX_TIME;
    esp_sleep_enable_timer_wakeup(wakeTimeUS);
    Serial.print("Wake timer set for ");
    Serial.print(seconds);
    Serial.println(" seconds.");
}

void printWakeupReason() {
    Serial.println("=================================");
    Serial.println("Sea Turtle Data Logger - Phase 1");
    Serial.println("=================================");

    esp_sleep_wakeup_cause_t reason = esp_sleep_get_wakeup_cause();
    switch (reason) {
        case ESP_SLEEP_WAKEUP_TIMER:
            Serial.println("Wakeup: Timer");
            break;

        case ESP_SLEEP_WAKEUP_UNDEFINED:
            Serial.println("Wakeup: Power-on Reset");
            break;

        case ESP_SLEEP_WAKEUP_EXT0:
            Serial.println("Wakeup: External GPIO");
            break;

        case ESP_SLEEP_WAKEUP_EXT1:
            Serial.println("Wakeup: External GPIO");
            break;

        default:
            Serial.print("Wakeup cause: ");
            Serial.println(reason);
            break;
    }
}
