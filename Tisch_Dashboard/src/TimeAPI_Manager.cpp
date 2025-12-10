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
// #include <Arduino_JSON.h>
#include <ArduinoJson.h>
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

#define DATETIME_EXAMPLE "\"2024-10-05T14:30:45Z\""
#define WEEKDAY_EXAMPLE "\"Monday\""

String timeAPI_buffer;
String weekdayApi_buffer;

// JSONVar timeAPI_JSON;
// JSONVar weekdayAPI_JSON;
JsonDocument timeAPI_JSON;
JsonDocument weekdayAPI_JSON;

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

        // TIME API REQUEST
        timeAPI_buffer = httpGETRequest(TIME_API_URL);

        timeAPI_JSON.clear();
        DeserializationError errorTime = deserializeJson(timeAPI_JSON, timeAPI_buffer);

        if (errorTime)
        {
            Serial.print("Datetime: Parsing input failed! Error: ");
            Serial.println(errorTime.c_str());
            Serial.println("using Example Data instead");
            dateTime = DATETIME_EXAMPLE;
            weekday = WEEKDAY_EXAMPLE;
            // return;
        }
        else
        {
            dateTime = timeAPI_JSON["datetime"].as<String>();
            Serial.println("Datetime: JSON parsed successfully!");
        }

        // WEEKDAY API REQUEST

        weekdayApi_buffer = httpGETRequest(WEEKDAY_API_URL);
        weekdayAPI_JSON.clear();
        DeserializationError errorWeekday = deserializeJson(weekdayAPI_JSON, weekdayApi_buffer);

        if (errorWeekday)
        {
            Serial.print("Weekday: Parsing input failed! Error: ");
            Serial.println(errorWeekday.c_str());
            Serial.println("using Example Data instead");
            weekday = WEEKDAY_EXAMPLE;
            // return;
        }
        else
        {
            weekday = weekdayAPI_JSON["result"].as<String>();
            Serial.println("Weekday: JSON parsed successfully!");
        }
    }
    else
    {
        Serial.println("WiFi Disconnected");
    }

// if (WiFi.status() == WL_CONNECTED)
// {
//     timeAPI_buffer = httpGETRequest(TIME_API_URL);
//     timeAPI_JSON = JSON.parse(timeAPI_buffer);

//     if (JSON.typeof(timeAPI_JSON) == "undefined")
//     {
//         Serial.println("Datetime: Parsing input failed!");
//         Serial.println("using Example Data instead");
//         dateTime = DATETIME_EXAMPLE;
//         weekday = WEEKDAY_EXAMPLE;
//         // return;
//     }
//     dateTime = JSON.stringify(timeAPI_JSON["datetime"]);

//     weekdayApi_buffer = httpGETRequest(WEEKDAY_API_URL);
//     weekdayAPI_JSON = JSON.parse(weekdayApi_buffer);
//     if (JSON.typeof(weekdayAPI_JSON) == "undefined")
//     {
//         Serial.println("Weekday: Parsing input failed!");
//         return;
//     }
//     weekday = JSON.stringify(weekdayAPI_JSON["result"]);
// }
// else
// {
//     Serial.println("WiFi Disconnected");
// }
#else
    dateTime = DATETIME_EXAMPLE;
    weekday = WEEKDAY_EXAMPLE;
#endif
}

void timeAPI_printTime()
{
    Serial.print("Current Time: ");
    Serial.print(timeAPI_JSON["datetime"].as<String>());
    Serial.print(", Weekday: ");
    Serial.print(weekdayAPI_JSON["result"].as<String>());
    Serial.println("");
}


#define STRING_INDEX_YEAR_START 0

uint16_t timeAPI_getYear()
{
    return (uint16_t)(((dateTime[STRING_INDEX_YEAR_START] & 0x0F) * 1000) +
                      ((dateTime[STRING_INDEX_YEAR_START + 1] & 0x0F) * 100) +
                      ((dateTime[STRING_INDEX_YEAR_START + 2] & 0x0F) * 10) +
                      (dateTime[STRING_INDEX_YEAR_START + 3] & 0x0F));
}

uint8_t timeAPI_getMonth()
{
    return (uint8_t)(((dateTime[STRING_INDEX_YEAR_START + 5] & 0x0F) * 10) +
                     (dateTime[STRING_INDEX_YEAR_START + 6] & 0x0F));
}

uint8_t timeAPI_getDay()
{
    return (uint8_t)(((dateTime[STRING_INDEX_YEAR_START + 8] & 0x0F) * 10) +
                     (dateTime[STRING_INDEX_YEAR_START + 9] & 0x0F));
}

uint8_t timeAPI_getHour()
{
    return (uint8_t)(((dateTime[STRING_INDEX_YEAR_START + 11] & 0x0F) * 10) +
                     (dateTime[STRING_INDEX_YEAR_START + 12] & 0x0F));
}

uint8_t timeAPI_getMinutes()
{
    return (uint8_t)(((dateTime[STRING_INDEX_YEAR_START + 14] & 0x0F) * 10) +
                     (dateTime[STRING_INDEX_YEAR_START + 15] & 0x0F));
}

uint8_t timeAPI_getSeconds()
{
    return (uint8_t)(((dateTime[STRING_INDEX_YEAR_START + 17] & 0x0F) * 10) +
                     (dateTime[STRING_INDEX_YEAR_START + 18] & 0x0F));
}

String timeAPI_getWeekday()
{
    return weekday;
}
