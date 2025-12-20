#ifndef RTC_MANAGER_H
#define RTC_MANAGER_H
// .----------------------------------------.
// | ___            _           _           |
// ||_ _|_ __   ___| |_   _  __| | ___  ___ |
// | | || '_ \ / __| | | | |/ _` |/ _ \/ __||
// | | || | | | (__| | |_| | (_| |  __/\__ \|
// ||___|_| |_|\___|_|\__,_|\__,_|\___||___/|
// '----------------------------------------'

// -------------------------------------------
// INCLUDES
// -------------------------------------------
#include <Wire.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>

#include "TimeAPI_Manager.h"

// -------------------------------------------
// KONSTANTEN & DEFINITIONEN
// -------------------------------------------

// -------------------------------------------
// Variabeln & Datentypen
// -------------------------------------------

// -------------------------------------------
// FUNKTIONSDEKLARATIONEN (globale Schnittstelle)
// -------------------------------------------
void rtc_init();
void rtc_updateTime();
void rtc_printTime();

uint8_t rtc_getSeconds();
uint8_t rtc_getMinutes();
uint8_t rtc_getHour();
uint8_t rtc_getDay();
uint8_t rtc_getMonth();
uint16_t rtc_getYear();
String rtc_getWeekday();
uint8_t rtc_getWeekdayIndex();

#endif // RTCMANAGER_H