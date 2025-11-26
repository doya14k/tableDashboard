#ifndef TIME_API_MANAGER_H
#define TIME_API_MANAGER_H

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
#include <Arduino.h>

// -------------------------------------------
// KONSTANTEN & DEFINITIONEN
// -------------------------------------------

// -------------------------------------------
// Variabeln & Datentypen
// -------------------------------------------


// -------------------------------------------
// FUNKTIONSDEKLARATIONEN (globale Schnittstelle)
// -------------------------------------------
void timeAPI_init();
void timeAPI_updateTime();
void timeAPI_printTime();

uint16_t timeAPI_getYear();
uint8_t timeAPI_getMonth();
uint8_t timeAPI_getDay();
uint8_t timeAPI_getHour();
uint8_t timeAPI_getMinutes();
uint8_t timeAPI_getSeconds();
String timeAPI_getWeekday();

#endif // TIME_API_MANAGER_H    