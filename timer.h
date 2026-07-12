#ifndef TIMER_H
#define TIMER_H

#include <cstdint>

void enterDeepSleep();
void setWakeTimer(uint32_t seconds = 3600);
void printWakeupReason();

#endif
