#ifndef WEATHER_API_MANAGER_H
#define WEATHER_API_MANAGER_H

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
// #include <Arduino.h>     // oder <iostream> für PC-Simulation

// -------------------------------------------
// KONSTANTEN & DEFINITIONEN
// -------------------------------------------
// #define MODULE_UPDATE_INTERVAL 60000  // 1 Minute

// -------------------------------------------
// Variabeln & Datentypen
// -------------------------------------------

// -------------------------------------------
// FUNKTIONSDEKLARATIONEN (globale Schnittstelle)
// -------------------------------------------
void weatherAPI_init();
void weatherAPI_updateWeatherData();
double weatherAPI_getCurrentTemperature();

#endif // WEATHER_API_MANAGER_H