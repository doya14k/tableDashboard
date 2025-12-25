#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H
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
#include "DEV_Config.h"
#include "EPD.h"
#include "GUI_Paint.h"
#include "fonts.h"
#include <stdlib.h>
#include "RTCManager.h"
#include "TempSensorManager.h"
#include "WeatherAPI_Manager.h"
#include "BusAPI_Manager.h"

// -------------------------------------------
// KONSTANTEN & DEFINITIONEN
// -------------------------------------------
// #define MODULE_UPDATE_INTERVAL 60000  // 1 Minute
#define DEGREE_CHAR 0x7F // Custom degree character code

// -------------------------------------------
// Variabeln & Datentypen
// -------------------------------------------

// -------------------------------------------
// FUNKTIONSDEKLARATIONEN (globale Schnittstelle)
// -------------------------------------------

void displayManager_init();
void displayManager_updateDisplay();
void displayManager_refreshDisplay();

#endif // DISPLAY_MANAGER_H