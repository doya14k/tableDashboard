#ifndef BUS_API_MANAGER_H
#define BUS_API_MANAGER_H

#include <Arduino.h>

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
void busAPI_init();
void busAPI_updateBusData();

int busAPI_getAvailableConnections();
String busAPI_getConnectionDepartureTime(int connectionIndex);
String busAPI_getConnectionArrivalTime(int connectionIndex);
String busAPI_getConnectionLine(int connectionIndex);
String busAPI_getConnectionTypeOfTransport(int connectionIndex);

String busAPI_getConnection_DepartureDestination();


#endif // BUS_API_MANAGER_H