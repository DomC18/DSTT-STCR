#include "rtc_manager.h"
#include "config.h"

RTC_DS3231 rtc;

bool initRTC() {
  if (!rtc.begin()) {
    return false;
  }
  // Uncomment ONCE to set RTC time
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  rtc.clearAlarm(1);
  rtc.clearAlarm(2);

  return true;
}

DateTime getCurrentTime() {
  return rtc.now();
}

void setNextAlarm() {
  rtc.clearAlarm(1);
  rtc.clearAlarm(2);

  DateTime now = rtc.now();
  int nextHour = now.hour() + 1;
  int nextDay = now.day();
  int nextMonth = now.month();
  int nextYear = now.year();

  if (nextHour >= 24) {
    nextHour = 0;
    DateTime tomorrow = now + TimeSpan(1, 0, 0, 0);
    nextDay = tomorrow.day();
    nextMonth = tomorrow.month();
    nextYear = tomorrow.year();
  }

  DateTime nextAlarm(nextYear, nextMonth, nextDay, nextHour, 0, 0);
  rtc.setAlarm1(nextAlarm, DS3231_A1_Hour);

  Serial.print("Next alarm: ");
  Serial.println(nextAlarm.timestamp());
}