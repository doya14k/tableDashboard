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
#include <Arduino.h> // oder <iostream> für PC-Simulation

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

// Current/Today Getter Funktionen
double weatherAPI_getCurrentTemperature();
double weatherAPI_getCurrentApparentTemperature();
bool weatherAPI_isDay();
int weatherAPI_getCurrentWeatherCode();
double weatherAPI_getCurrentWindSpeed();
int weatherAPI_getCurrentWindDirection();
double weatherAPI_getCurrentRelativeHumidity();
int weatherAPI_getCurrentCloudCover();
double weatherAPI_getCurrentShowers();
double weatherAPI_getCurrentRain();
double weatherAPI_getCurrentSnowfall();
double weatherAPI_getCurrentPrecipitation();

// Hourly Getter Funktionen
double weatherAPI_getHourlyTemperature(int hourIndex);
double weatherAPI_getHourlyApparentTemperature(int hourIndex);
int weatherAPI_getHourlyWeatherCode(int hourIndex);
double weatherAPI_getHourlyPrecipitation(int hourIndex);
double weatherAPI_getHourlyRain(int hourIndex);
double weatherAPI_getHourlySnowfall(int hourIndex);
double weatherAPI_getHourlySnowDepth(int hourIndex);

// Daily Getter Funktionen
double weatherAPI_getDailyMaxTemperature(int dayIndex);
double weatherAPI_getDailyMinTemperature(int dayIndex);
String weatherAPI_getDailySunriseTime(int dayIndex);
String weatherAPI_getDailySunsetTime(int dayIndex);
int weatherAPI_getDailyWeatherCode(int dayIndex);
double weatherAPI_getDailyPrecipitationSum(int dayIndex);
double weatherAPI_getDailyRainSum(int dayIndex);
double weatherApi_getDailySnowfallSum(int dayIndex);

#endif // WEATHER_API_MANAGER_H