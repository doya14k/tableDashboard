#ifndef TEMP_SENSOR_MANAGER_H
#define TEMP_SENSOR_MANAGER_H

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
void tempSensor_init();

float tempSensor_getTemperature();

#endif // TEMP_SENSOR_MANAGER_H