// .----------------------------------------.
// | ___            _           _           |
// ||_ _|_ __   ___| |_   _  __| | ___  ___ |
// | | || '_ \ / __| | | | |/ _` |/ _ \/ __||
// | | || | | | (__| | |_| | (_| |  __/\__ \|
// ||___|_| |_|\___|_|\__,_|\__,_|\___||___/|
// '----------------------------------------'
#include "TimeAPI_Manager.h"

#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include "main.h"
// .----------------------------------.
// | ____        __ _                 |
// ||  _ \  ___ / _(_)_ __   ___  ___ |
// || | | |/ _ \ |_| | '_ \ / _ \/ __||
// || |_| |  __/  _| | | | |  __/\__ \|
// ||____/ \___|_| |_|_| |_|\___||___/|
// '----------------------------------'
#define TIME_API_URL "https://aisenseapi.com/services/v1/datetime/0100"

const char *ssid = "brz-63878";
const char *password = "eqao-25ds-iry4-8imk";
const char *weatherApiUrl;

String timeAPI_buffer;

JSONVar timeAPI_JSON;

String dateTime;
// .---------------------------------------------.
// | _____                 _   _                 |
// ||  ___|   _ _ __   ___| |_(_) ___  _ __  ___ |
// || |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __||
// ||  _|| |_| | | | | (__| |_| | (_) | | | \__ \|
// ||_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/|
// '---------------------------------------------'

void timeAPI_init()
{
    // Wifi initialize
    WiFi.begin(ssid, password);
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());

    timeAPI_updateTime();
}

void timeAPI_updateTime()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        timeAPI_buffer = httpGETRequest(TIME_API_URL);
        timeAPI_JSON = JSON.parse(timeAPI_buffer);

        if (JSON.typeof(timeAPI_JSON) == "undefined")
        {
            Serial.println("Parsing input failed!");
            return;
        }

        dateTime = JSON.stringify(timeAPI_JSON["datetime"]);
    }
    else
    {
        Serial.println("WiFi Disconnected");
    }
}

void timeAPI_printTime()
{
    Serial.print("Current Time: ");
    Serial.print(timeAPI_JSON["datetime"]);
    Serial.println("");
}

uint16_t timeAPI_getYear()
{
    return (uint16_t)((dateTime[1] & 0x0F) * 1000) + ((dateTime[2] & 0x0F) * 100) + ((dateTime[3] & 0x0F) * 10) + (dateTime[4] & 0x0F);
}

uint8_t timeAPI_getMonth()
{
    return (uint8_t)((dateTime[6] & 0x0F) * 10) + (dateTime[7] & 0x0F);
}

uint8_t timeAPI_getDay()
{
    return (uint8_t)((dateTime[9] & 0x0F) * 10) + (dateTime[10] & 0x0F);
}

uint8_t timeAPI_getHour()
{
    return (uint8_t)((dateTime[12] & 0x0F) * 10) + (dateTime[13] & 0x0F);
}

uint8_t timeAPI_getMinutes()
{
    return (uint8_t)((dateTime[15] & 0x0F) * 10) + (dateTime[16] & 0x0F);
}

uint8_t timeAPI_getSeconds()
{
    return (uint8_t)((dateTime[18] & 0x0F) * 10) + (dateTime[19] & 0x0F);
}