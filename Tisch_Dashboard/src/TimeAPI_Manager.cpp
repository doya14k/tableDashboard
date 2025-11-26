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

#define USE_TIME_API

#define TIME_API_URL "https://aisenseapi.com/services/v1/datetime/+0100"
#define WEEKDAY_API_URL "https://api.datesapi.net/today?format=Monday"

String timeAPI_buffer;
String weekdayApi_buffer;

JSONVar timeAPI_JSON;
JSONVar weekdayAPI_JSON;

String dateTime;
String weekday;
// .---------------------------------------------.
// | _____                 _   _                 |
// ||  ___|   _ _ __   ___| |_(_) ___  _ __  ___ |
// || |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __||
// ||  _|| |_| | | | | (__| |_| | (_) | | | \__ \|
// ||_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/|
// '---------------------------------------------'

void timeAPI_init()
{
    timeAPI_updateTime();
}

void timeAPI_updateTime()
{
#ifdef USE_TIME_API
    if (WiFi.status() == WL_CONNECTED)
    {
        timeAPI_buffer = httpGETRequest(TIME_API_URL);
        timeAPI_JSON = JSON.parse(timeAPI_buffer);

        if (JSON.typeof(timeAPI_JSON) == "undefined")
        {
            Serial.println("Datetime: Parsing input failed!");
            return;
        }
        dateTime = JSON.stringify(timeAPI_JSON["datetime"]);

        weekdayApi_buffer = httpGETRequest(WEEKDAY_API_URL);
        weekdayAPI_JSON = JSON.parse(weekdayApi_buffer);
        if (JSON.typeof(weekdayAPI_JSON) == "undefined")
        {
            Serial.println("Weekday: Parsing input failed!");
            return;
        }
        weekday = JSON.stringify(weekdayAPI_JSON["result"]);
    }
    else
    {
        Serial.println("WiFi Disconnected");
    }
#else
    dateTime = "\"2024-10-05T14:30:45Z\"";
    weekday = "Monday";
#endif
}

void timeAPI_printTime()
{
    Serial.print("Current Time: ");
    Serial.print(timeAPI_JSON["datetime"]);
    Serial.print(", Weekday: ");
    Serial.print(weekdayAPI_JSON["result"]);
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

String timeAPI_getWeekday()
{
    return weekday;
}