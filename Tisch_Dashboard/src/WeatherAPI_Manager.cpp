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

#define PRINT_OUT_DATA

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

// .-----------------------------------------------------------------------.
// | _____         _              __        __         _   _               |
// ||_   _|__   __| | __ _ _   _  \ \      / /__  __ _| |_| |__   ___ _ __ |
// |  | |/ _ \ / _` |/ _` | | | |  \ \ /\ / / _ \/ _` | __| '_ \ / _ \ '__||
// |  | | (_) | (_| | (_| | |_| |   \ V  V /  __/ (_| | |_| | | |  __/ |   |
// | _|_|\___/ \__,_|\__,_|\__, |    \_/\_/ \___|\__,_|\__|_| |_|\___|_|   |
// ||  _ \  __ _| |_ __ _  |___/                                           |
// || | | |/ _` | __/ _` |                                                 |
// || |_| | (_| | || (_| |                                                 |
// ||____/ \__,_|\__\__,_|                                                 |
// '-----------------------------------------------------------------------'

double weatherAPI_getCurrentTemperature()
{
#ifdef PRINT_OUT_DATA
    Serial.print("Temperature_2m ");
    Serial.print(weatherAPI_JSON["current"]["temperature_2m"].as<String>());
    Serial.println("°C");
#endif // PRINT_OUT_DATA
    return weatherAPI_JSON["current"]["temperature_2m"].as<double>();
}

double weatherAPI_getCurrentApparentTemperature()
{
#ifdef PRINT_OUT_DATA
    Serial.print("apparent_Temperature ");
    Serial.print(weatherAPI_JSON["current"]["apparent_temperature"].as<String>());
    Serial.println("°C");
#endif // PRINT_OUT_DATA
    return weatherAPI_JSON["current"]["apparent_temperature"].as<double>();
}

bool weatherAPI_isDay()
{
#ifdef PRINT_OUT_DATA
    Serial.print("is_day ");
    Serial.print(weatherAPI_JSON["current"]["is_day"].as<String>());
    Serial.println("");
#endif // PRINT_OUT_DATA
    return (bool)weatherAPI_JSON["current"]["is_day"].as<bool>();
}

int weatherAPI_getCurrentWeatherCode()
{
#ifdef PRINT_OUT_DATA
    Serial.print("weather_code ");
    Serial.print(weatherAPI_JSON["current"]["weather_code"].as<String>());
    Serial.println("");
#endif // PRINT_OUT_DATA
    return (int)weatherAPI_JSON["current"]["apparent_temperature"].as<int>();
}

double weatherAPI_getCurrentWindSpeed()
{
#ifdef PRINT_OUT_DATA
    Serial.print("wind_speed_10m ");
    Serial.print(weatherAPI_JSON["current"]["wind_speed_10m"].as<String>());
    Serial.println("km/h");
#endif // PRINT_OUT_DATA
    return weatherAPI_JSON["current"]["wind_speed_10m"].as<double>();
}

int weatherAPI_getCurrentWindDirection()
{
#ifdef PRINT_OUT_DATA
    Serial.print("wind_direction_10m ");
    Serial.print(weatherAPI_JSON["current"]["wind_direction_10m"].as<String>());
    Serial.println("°");
#endif // PRINT_OUT_DATA
    return (int)weatherAPI_JSON["current"]["wind_direction_10m"].as<int>();
}

double weatherAPI_getCurrentRelativeHumidity()
{
#ifdef PRINT_OUT_DATA
    Serial.print("relative_humidity_2m ");
    Serial.print(weatherAPI_JSON["current"]["relative_humidity_2m"].as<String>());
    Serial.println("%");
#endif // PRINT_OUT_DATA
    return weatherAPI_JSON["current"]["relative_humidity_2m"].as<double>();
}

int weatherAPI_getCurrentCloudCover()
{
#ifdef PRINT_OUT_DATA
    Serial.print("cloud_cover ");
    Serial.print(weatherAPI_JSON["current"]["cloud_cover"].as<String>());
    Serial.println("%");
#endif // PRINT_OUT_DATA
    return (int)weatherAPI_JSON["current"]["cloud_cover"].as<int>();
}

double weatherAPI_getCurrentShowers()
{
#ifdef PRINT_OUT_DATA
    Serial.print("showers ");
    Serial.print(weatherAPI_JSON["current"]["showers"].as<String>());
    Serial.println("mm");
#endif // PRINT_OUT_DATA
    return weatherAPI_JSON["current"]["showers"].as<double>();
}

double weatherAPI_getCurrentRain()
{
#ifdef PRINT_OUT_DATA
    Serial.print("rain ");
    Serial.print(weatherAPI_JSON["current"]["rain"].as<String>());
    Serial.println("mm");
#endif // PRINT_OUT_DATA
    return weatherAPI_JSON["current"]["rain"].as<double>();
}

double weatherAPI_getCurrentSnowfall()
{
#ifdef PRINT_OUT_DATA
    Serial.print("snowfall ");
    Serial.print(weatherAPI_JSON["current"]["snowfall"].as<String>());
    Serial.println("cm");
#endif // PRINT_OUT_DATA
    return weatherAPI_JSON["current"]["snowfall"].as<double>();
}

double weatherAPI_getCurrentPrecipitation()
{
#ifdef PRINT_OUT_DATA
    Serial.print("precipitation ");
    Serial.print(weatherAPI_JSON["current"]["precipitation"].as<String>());
    Serial.println("mm");
#endif // PRINT_OUT_DATA
    return weatherAPI_JSON["current"]["precipitation"].as<double>();
}

// .--------------------------------------------------------------------------.
// | _   _                  _        __        __         _   _               |
// || | | | ___  _   _ _ __| |_   _  \ \      / /__  __ _| |_| |__   ___ _ __ |
// || |_| |/ _ \| | | | '__| | | | |  \ \ /\ / / _ \/ _` | __| '_ \ / _ \ '__||
// ||  _  | (_) | |_| | |  | | |_| |   \ V  V /  __/ (_| | |_| | | |  __/ |   |
// ||_|_|_|\___/ \__,_|_|  |_|\__, |    \_/\_/ \___|\__,_|\__|_| |_|\___|_|   |
// ||  _ \  __ _| |_ __ _     |___/                                           |
// || | | |/ _` | __/ _` |                                                    |
// || |_| | (_| | || (_| |                                                    |
// ||____/ \__,_|\__\__,_|                                                    |
// '--------------------------------------------------------------------------'

double weatherAPI_getHourlyTemperature(int hourIndex)
{
#ifdef PRINT_OUT_DATA
    Serial.print("Temperature at hourIndex ");
    Serial.print(hourIndex);
    Serial.print(": ");
    Serial.print(weatherAPI_JSON["hourly"]["temperature_2m"][hourIndex].as<String>());
    Serial.println("°C");
#endif // PRINT_OUT_DATA
    return weatherAPI_JSON["hourly"]["temperature_2m"][hourIndex].as<double>();
}

double weatherAPI_getHourlyApparentTemperature(int hourIndex)
{
#ifdef PRINT_OUT_DATA
    Serial.print("ApparentTemperature at hourIndex ");
    Serial.print(hourIndex);
    Serial.print(": ");
    Serial.print(weatherAPI_JSON["hourly"]["apparent_temperature"][hourIndex].as<String>());
    Serial.println("°C");
#endif // PRINT_OUT_DATA
    return weatherAPI_JSON["hourly"]["apparent_temperature"][hourIndex].as<double>();
}

int weatherAPI_getHourlyWeatherCode(int hourIndex)
{
#ifdef PRINT_OUT_DATA
    Serial.print("weather_code at hourIndex ");
    Serial.print(hourIndex);
    Serial.print(": ");
    Serial.print(weatherAPI_JSON["hourly"]["weather_code"][hourIndex].as<String>());
    Serial.println("");
#endif // PRINT_OUT_DATA
    return weatherAPI_JSON["hourly"]["weather_code"][hourIndex].as<int>();
}

double weatherAPI_getHourlyPrecipitation(int hourIndex)
{
#ifdef PRINT_OUT_DATA
    Serial.print("Precipitation at hourIndex ");
    Serial.print(hourIndex);
    Serial.print(": ");
    Serial.print(weatherAPI_JSON["hourly"]["precipitation"][hourIndex].as<String>());
    Serial.println("mm");
#endif // PRINT_OUT_DATA
    return weatherAPI_JSON["hourly"]["precipitation"][hourIndex].as<double>();
}

double weatherAPI_getHourlyRain(int hourIndex)
{
#ifdef PRINT_OUT_DATA
    Serial.print("Rain at hourIndex ");
    Serial.print(hourIndex);
    Serial.print(": ");
    Serial.print(weatherAPI_JSON["hourly"]["rain"][hourIndex].as<String>());
    Serial.println("mm");
#endif // PRINT_OUT_DATA
    return weatherAPI_JSON["hourly"]["rain"][hourIndex].as<double>();
}

double weatherAPI_getHourlySnowfall(int hourIndex)
{
#ifdef PRINT_OUT_DATA
    Serial.print("Snowfall at hourIndex ");
    Serial.print(hourIndex);
    Serial.print(": ");
    Serial.print(weatherAPI_JSON["hourly"]["snowfall"][hourIndex].as<String>());
    Serial.println("cm");
#endif // PRINT_OUT_DATA
    return weatherAPI_JSON["hourly"]["snowfall"][hourIndex].as<double>();
}

double weatherAPI_getHourlySnowDepth(int hourIndex)
{
#ifdef PRINT_OUT_DATA
    Serial.print("Snow-Depth at hourIndex ");
    Serial.print(hourIndex);
    Serial.print(": ");
    Serial.print(weatherAPI_JSON["hourly"]["snowfall"][hourIndex].as<String>());
    Serial.println("m");
#endif // PRINT_OUT_DATA
    return weatherAPI_JSON["hourly"]["snowfall"][hourIndex].as<double>();
}

// .-----------------------------------------------------------------.
// | ____        _ _        __        __         _   _               |
// ||  _ \  __ _(_) |_   _  \ \      / /__  __ _| |_| |__   ___ _ __ |
// || | | |/ _` | | | | | |  \ \ /\ / / _ \/ _` | __| '_ \ / _ \ '__||
// || |_| | (_| | | | |_| |   \ V  V /  __/ (_| | |_| | | |  __/ |   |
// ||____/ \__,_|_|_|\__, |    \_/\_/ \___|\__,_|\__|_| |_|\___|_|   |
// ||  _ \  __ _| |_ |___/                                           |
// || | | |/ _` | __/ _` |                                           |
// || |_| | (_| | || (_| |                                           |
// ||____/ \__,_|\__\__,_|                                           |
// '-----------------------------------------------------------------'

double weatherAPI_getDailyMaxTemperature(int dayIndex)
{
#ifdef PRINT_OUT_DATA
    Serial.print("Todays Max Temperature at dayIndex ");
    Serial.print(dayIndex);
    Serial.print(": ");
    Serial.print(weatherAPI_JSON["daily"]["temperature_2m_max"][dayIndex].as<String>());
    Serial.println("°C");
#endif // PRINT_OUT_DATA
    return weatherAPI_JSON["daily"]["temperature_2m_max"][dayIndex].as<double>();
}

double weatherAPI_getDailyMinTemperature(int dayIndex)
{
#ifdef PRINT_OUT_DATA
    Serial.print("Todays Min Temperature at dayIndex");
    Serial.print(dayIndex);
    Serial.print(": ");
    Serial.print(weatherAPI_JSON["daily"]["temperature_2m_min"][dayIndex].as<String>());
    Serial.println("°C");
#endif // PRINT_OUT_DATA
    return weatherAPI_JSON["daily"]["temperature_2m_min"][dayIndex].as<double>();
}

String weatherAPI_getDailySunriseTime(int dayIndex)
{
    String sunriseTimeHH_MM = weatherAPI_JSON["daily"]["sunrise"][dayIndex].as<String>();

    uint8_t positionOf_T = weatherAPI_JSON["daily"]["sunrise"][dayIndex].as<String>().indexOf('T');
    sunriseTimeHH_MM.remove(0, positionOf_T + 1);

#ifdef PRINT_OUT_DATA
    Serial.print("Todays Sunrise Time at dayIndex ");
    Serial.print(dayIndex);
    Serial.print(": ");
    Serial.print(sunriseTimeHH_MM);
    Serial.println("");
#endif // PRINT_OUT_DATA
    return sunriseTimeHH_MM;
}

String weatherAPI_getDailySunsetTime(int dayIndex)
{
    String sunsetTimeHH_MM = weatherAPI_JSON["daily"]["sunset"][dayIndex].as<String>();

    uint8_t positionOf_T = weatherAPI_JSON["daily"]["sunset"][dayIndex].as<String>().indexOf('T');
    sunsetTimeHH_MM.remove(0, positionOf_T + 1);

#ifdef PRINT_OUT_DATA
    Serial.print("Todays Sunset Time at dayIndex ");
    Serial.print(dayIndex);
    Serial.print(": ");
    Serial.print(sunsetTimeHH_MM);
    Serial.println("");
#endif // PRINT_OUT_DATA
    return sunsetTimeHH_MM;
}

int weatherAPI_getDailyWeatherCode(int dayIndex)
{
#ifdef PRINT_OUT_DATA
    Serial.print("Todays WeatherCode at dayIndex ");
    Serial.print(dayIndex);
    Serial.print(": ");
    Serial.print(weatherAPI_JSON["daily"]["weather_code"][dayIndex].as<String>());
    Serial.println("");
#endif // PRINT_OUT_DATA
    return weatherAPI_JSON["daily"]["weather_code"][dayIndex].as<int>();
}

double weatherAPI_getDailyPrecipitationSum(int dayIndex)
{
#ifdef PRINT_OUT_DATA
    Serial.print("Todays Precipitation Sum at dayIndex ");
    Serial.print(dayIndex);
    Serial.print(": ");
    Serial.print(weatherAPI_JSON["daily"]["precipitation_sum"][dayIndex].as<String>());
    Serial.println("mm");
#endif // PRINT_OUT_DATA
    return weatherAPI_JSON["daily"]["precipitation_sum"][dayIndex].as<double>();
}

double weatherAPI_getDailyRainSum(int dayIndex)
{
#ifdef PRINT_OUT_DATA
    Serial.print("Todays Rain Sum at dayIndex ");
    Serial.print(dayIndex);
    Serial.print(": ");
    Serial.print(weatherAPI_JSON["daily"]["rain_sum"][dayIndex].as<String>());
    Serial.println("mm");
#endif // PRINT_OUT_DATA
    return weatherAPI_JSON["daily"]["rain_sum"][dayIndex].as<double>();
}

double weatherApi_getDailySnowfallSum(int dayIndex)
{
#ifdef PRINT_OUT_DATA
    Serial.print("Todays Snowfall Sum at dayIndex ");
    Serial.print(dayIndex);
    Serial.print(": ");
    Serial.print(weatherAPI_JSON["daily"]["snowfall_sum"][dayIndex].as<String>());
    Serial.println("cm");
#endif // PRINT_OUT_DATA
    return weatherAPI_JSON["daily"]["snowfall_sum"][dayIndex].as<double>();
}