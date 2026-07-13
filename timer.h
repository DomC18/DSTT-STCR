#ifndef TIMER_H
#define TIMER_H

#include <cstdint>

void enterDeepSleep();
void setWakeTimer(bool isSurfaced);
void printWakeupReason();

#endif
