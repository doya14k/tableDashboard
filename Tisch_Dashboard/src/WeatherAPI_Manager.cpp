// .----------------------------------------.
// | ___            _           _           |
// ||_ _|_ __   ___| |_   _  __| | ___  ___ |
// | | || '_ \ / __| | | | |/ _` |/ _ \/ __||
// | | || | | | (__| | |_| | (_| |  __/\__ \|
// ||___|_| |_|\___|_|\__,_|\__,_|\___||___/|
// '----------------------------------------'

#include "WeatherAPI_Manager.h"
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

#define WEATHER_API_URL "http://api.open-meteo.com/v1/forecast?latitude=46.8499&longitude=9.5329&daily=weather_code,temperature_2m_max,apparent_temperature_max,temperature_2m_min,apparent_temperature_min,sunshine_duration,sunset,sunrise,daylight_duration,rain_sum,showers_sum,snowfall_sum,precipitation_hours,precipitation_sum,precipitation_probability_max,wind_speed_10m_max,wind_gusts_10m_max,wind_direction_10m_dominant,shortwave_radiation_sum,et0_fao_evapotranspiration&hourly=temperature_2m,relative_humidity_2m,dew_point_2m,apparent_temperature,precipitation,rain,snowfall,snow_depth,evapotranspiration,et0_fao_evapotranspiration,vapour_pressure_deficit,weather_code&models=meteoswiss_icon_ch2&current=temperature_2m,relative_humidity_2m,apparent_temperature,is_day,wind_speed_10m,wind_direction_10m,wind_gusts_10m,weather_code,cloud_cover,pressure_msl,surface_pressure,showers,snowfall,rain,precipitation&timezone=Europe%2FBerlin&forecast_days=7"

const char *weatherApiUrl;

String weatherAPI_buffer;

// JSONVar weatherAPI_JSON;
JsonDocument weatherAPI_JSON;

// .---------------------------------------------.
// | _____                 _   _                 |
// ||  ___|   _ _ __   ___| |_(_) ___  _ __  ___ |
// || |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __||
// ||  _|| |_| | | | | (__| |_| | (_) | | | \__ \|
// ||_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/|
// '---------------------------------------------'

void weatherAPI_init()
{
    weatherAPI_updateWeatherData();
}

void weatherAPI_updateWeatherData()
{

    if (WiFi.status() == WL_CONNECTED)
    {
        weatherAPI_buffer = httpGETRequest(WEATHER_API_URL);

        weatherAPI_JSON.clear();
        DeserializationError error = deserializeJson(weatherAPI_JSON, weatherAPI_buffer);

        if (error)
        {
            Serial.print("Weather API: Parsing input failed! Error: ");
            Serial.println(error.c_str());
            return;
        }

        Serial.println("Weather API: JSON parsed successfully!");
    }
    else
    {
        Serial.println("WiFi Disconnected");
    }
}

double weatherAPI_getCurrentTemperature()
{
    // funktioniert hier nicht mit der ausgabe (null)
    Serial.print("Temperature ");
    Serial.print(weatherAPI_JSON["current"]["temperature_2m"].as<float>());
    Serial.println("°C");
    return (double)weatherAPI_JSON["current"]["temperature_2m"];
}