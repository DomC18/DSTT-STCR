#include "esp_sleep.h"

#include "power_manager.h"
#include "config.h"

void enterDeepSleep() {
    esp_sleep_enable_timer_wakeup(30000);
    esp_deep_sleep_start();
}