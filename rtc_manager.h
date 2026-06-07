#ifndef RTC_MANAGER_H
#define RTC_MANAGER_H

#include <RTClib.h>

extern RTC_DS3231 rtc;

bool initRTC();
void setNextAlarm();
DateTime getCurrentTime();

#endif