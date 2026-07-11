#include "timer.h"

#include <Arduino.h>
#include <esp_sleep.h>

void setWakeTimer(uint32_t seconds) {
    uint64_t wakeTimeUS = (uint64_t)seconds * 1000000ULL;
    esp_sleep_enable_timer_wakeup(wakeTimeUS);

    Serial.print("Wake timer set for ");
    Serial.print(seconds);
    Serial.println(" seconds.");
}

void printWakeupReason() {
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