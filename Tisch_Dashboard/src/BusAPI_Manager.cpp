// .----------------------------------------.
// | ___            _           _           |
// ||_ _|_ __   ___| |_   _  __| | ___  ___ |
// | | || '_ \ / __| | | | |/ _` |/ _ \/ __||
// | | || | | | (__| | |_| | (_| |  __/\__ \|
// ||___|_| |_|\___|_|\__,_|\__,_|\___||___/|
// '----------------------------------------'

#include "BusAPI_Manager.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "main.h"

// .----------------------------------.
// | ____        __ _                 |
// ||  _ \  ___ / _(_)_ __   ___  ___ |
// || | | |/ _ \ |_| | '_ \ / _ \/ __||
// || |_| |  __/  _| | | | |  __/\__ \|
// ||____/ \___|_| |_|_| |_|\___||___/|
// '----------------------------------'

// 1000 requests per day
#define BUS_API_URL_VIEGA_CH "https://search.ch/fahrplan/api/route.json?from=Chur,+La-Nicca-Strasse-12&to=Chur"
#define BUS_API_URL_HOME "https://search.ch/fahrplan/api/route.json?from=Chur,+Stelleweg+27A&to=Chur"

#define PRINT_OUT_DATA

const char *busApiUrl;

String busAPI_buffer;

// JSONVar weatherAPI_JSON;
JsonDocument busAPI_JSON;

// .---------------------------------------------.
// | _____                 _   _                 |
// ||  ___|   _ _ __   ___| |_(_) ___  _ __  ___ |
// || |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __||
// ||  _|| |_| | | | | (__| |_| | (_) | | | \__ \|
// ||_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/|
// '---------------------------------------------'

void busAPI_init()
{
    busAPI_updateBusData();
}

void busAPI_updateBusData()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        busAPI_buffer = httpGETRequest(BUS_API_URL_VIEGA_CH);

        busAPI_JSON.clear();
        DeserializationError error = deserializeJson(busAPI_JSON, busAPI_buffer);

        if (error)
        {
            Serial.print("Bus API: Parsing input failed! Error: ");
            Serial.println(error.c_str());
            return;
        }

        Serial.println("Bus API: JSON parsed successfully!");
    }
    else
    {
        Serial.println("WiFi Disconnected");
    }
}

// .------------------------------------.
// | ____                 _    ____ ___ |
// || __ ) _   _ ___     / \  |  _ \_ _||
// ||  _ \| | | / __|   / _ \ | |_) | | |
// || |_) | |_| \__ \  / ___ \|  __/| | |
// ||____/ \__,_|___/ /_/   \_\_|  |___||
// '------------------------------------'

int busAPI_getAvailableConnections()
{
#ifdef PRINT_OUT_DATA
    Serial.print("available connections count: ");
    Serial.println(busAPI_JSON["count"].as<String>());
#endif // PRINT_OUT_DATA
    return busAPI_JSON["count"].as<int>();
}

String busAPI_getConnectionDepartureTime(int connectionIndex)
{
    String departureTimeHH_MM = busAPI_JSON["connections"][connectionIndex]["legs"][1]["departure"].as<String>();
    uint8_t positionOf_SPACE = busAPI_JSON["connections"][connectionIndex]["legs"][1]["departure"].as<String>().indexOf(' ');
    departureTimeHH_MM.remove(0, positionOf_SPACE + 1);
    departureTimeHH_MM.remove(5, 3); // remove seconds
#ifdef PRINT_OUT_DATA
    Serial.print("Connection Departure Time at connectionIndex ");
    Serial.print(connectionIndex);
    Serial.print(": ");
    Serial.print(departureTimeHH_MM);
    Serial.println("");
#endif // PRINT_OUT_DATA
    return departureTimeHH_MM.c_str();
}

String busAPI_getConnectionArrivalTime(int connectionIndex)
{
    String arrivalTimeHH_MM = busAPI_JSON["connections"][connectionIndex]["legs"][2]["arrival"].as<String>();
    uint8_t positionOf_SPACE = busAPI_JSON["connections"][connectionIndex]["legs"][2]["arrival"].as<String>().indexOf(' ');
    arrivalTimeHH_MM.remove(0, positionOf_SPACE + 1);
    arrivalTimeHH_MM.remove(5, 3); // remove seconds
#ifdef PRINT_OUT_DATA
    Serial.print("Connection Arrival Time at connectionIndex ");
    Serial.print(connectionIndex);
    Serial.print(": ");
    Serial.print(arrivalTimeHH_MM);
    Serial.println("");
#endif // PRINT_OUT_DATA
    return arrivalTimeHH_MM.c_str();
}

String busAPI_getConnectionLine(int connectionIndex)
{
    String line = busAPI_JSON["connections"][connectionIndex]["legs"][1]["line"].as<String>();
#ifdef PRINT_OUT_DATA
    Serial.print("Connection Line at connectionIndex ");
    Serial.print(connectionIndex);
    Serial.print(": ");
    Serial.print(line);
    Serial.println("");
#endif // PRINT_OUT_DATA
    return line.c_str();
}

String busAPI_getConnectionTypeOfTransport(int connectionIndex)
{
    String typeOfTransport = busAPI_JSON["connections"][connectionIndex]["legs"][1]["type"].as<String>();
#ifdef PRINT_OUT_DATA
    Serial.print("Connection Type of Transport at connectionIndex ");
    Serial.print(connectionIndex);
    Serial.print(": ");
    Serial.print(typeOfTransport);
    Serial.println("");
#endif // PRINT_OUT_DATA
    return typeOfTransport.c_str();
}

String busAPI_getConnection_DepartureDestination()
{
    String departureDestination = busAPI_JSON["points"][0]["text"].as<String>();
    // departureDestination.remove(0, departureDestination.indexOf(',') + 2); // remove everything before the ',  ' part that is most likely "Chur, "
#ifdef PRINT_OUT_DATA
    Serial.print("Connection Departure Destination: ");
    Serial.print(departureDestination);
    Serial.println("");
#endif // PRINT_OUT_DATA
    return departureDestination.c_str();
}