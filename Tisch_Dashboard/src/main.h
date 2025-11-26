#ifndef MAIN_H
#define MAIN_H

// .----------------------------------------.
// | ___            _           _           |
// ||_ _|_ __   ___| |_   _  __| | ___  ___ |
// | | || '_ \ / __| | | | |/ _` |/ _ \/ __||
// | | || | | | (__| | |_| | (_| |  __/\__ \|
// ||___|_| |_|\___|_|\__,_|\__,_|\___||___/|
// '----------------------------------------'

#include "BusAPI_Manager.h"
#include "DisplayManager.h"
#include "RTCManager.h"
#include "TempSensorManager.h"
#include "TouchManager.h"
#include "WeatherAPI_Manager.h"
#include "TimeAPI_Manager.h"
#include "WifiManager.h"

// .--------------------------------------------.
// | ____  _             _                ___   |
// ||  _ \(_)_ __  _ __ (_)_ __   __ _   ( _ )  |
// || |_) | | '_ \| '_ \| | '_ \ / _` |  / _ \/\|
// ||  __/| | | | | | | | | | | | (_| | | (_>  <|
// ||_|__ |_|_| |_|_| |_|_|_| |_|\__, |  \___/\/|
// ||  _ \  ___ / _(_)_ __   ___ |___/          |
// || | | |/ _ \ |_| | '_ \ / _ \/ __|          |
// || |_| |  __/  _| | | | |  __/\__ \          |
// ||____/ \___|_| |_|_| |_|\___||___/          |
// '--------------------------------------------'

// .----------------------------------------.
// | _____      ____                        |
// || ____|    |  _ \ __ _ _ __   ___ _ __  |
// ||  _| _____| |_) / _` | '_ \ / _ \ '__| |
// || |__|_____|  __/ (_| | |_) |  __/ |    |
// ||_____|    |_|   \__,_| .__/ \___|_|    |
// |                      |_|               |
// '----------------------------------------'
/*
#define EPD_SCK_PIN  18 // 13
#define EPD_MOSI_PIN 23 // 14
#define EPD_CS_PIN   15
#define EPD_RST_PIN  26
#define EPD_DC_PIN   27
#define EPD_BUSY_PIN 25
*/

#define SPI_MISO_PIN 19

// #define DEGREE_CHAR "0x7F" // Custom degree character code

// .-----------------.
// | ___ ____   ____ |
// ||_ _|___ \ / ___||
// | | |  __) | |    |
// | | | / __/| |___ |
// ||___|_____|\____||
// '-----------------'

#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22

// .--------------------------------------------.
// | _____                _       ____  _       |
// ||_   _|__  _   _  ___| |__   |  _ \(_)_ __  |
// |  | |/ _ \| | | |/ __| '_ \  | |_) | | '_ \ |
// |  | | (_) | |_| | (__| | | | |  __/| | | | ||
// |  |_|\___/ \__,_|\___|_| |_| |_|   |_|_| |_||
// '--------------------------------------------'

#define TOUCH_LEFT 2
#define TOUCH_MIDDLE 0
#define TOUCH_RIGHT 4
#define TOUCH_DOWN 13
#define TOUCH_UP 12

#define TOUCH_THRESHOLD 40

// .----------------------------------------------.
// |       ____  ____         ____              _ |
// | _   _/ ___||  _ \       / ___|__ _ _ __ __| ||
// || | | \___ \| | | |_____| |   / _` | '__/ _` ||
// || |_| |___) | |_| |_____| |__| (_| | | | (_| ||
// || ._,_|____/|____/       \____\__,_|_|  \__,_||
// ||_|                                           |
// '----------------------------------------------'

#define CD1_PIN 14
#define CS_SD_CARD_PIN 8

// API URL --> to be moved to its module

// #define WEATER_API_VERSIONS "https://www.meteoschweiz.admin.ch/product/output/versions.json"

// #define SRF_WEATHER_API_URL "https://www.srf.ch/meteoapi/forecastpoint/46.8507,9.5317"

#define OPEN_METEO_WEATHER_API_URL "https://api.open-meteo.com/v1/forecast?latitude=46.8499&longitude=9.5329&daily=weather_code,temperature_2m_max,apparent_temperature_max,temperature_2m_min,apparent_temperature_min,sunshine_duration,sunset,sunrise,daylight_duration,rain_sum,showers_sum,snowfall_sum,precipitation_hours,precipitation_sum,precipitation_probability_max,wind_speed_10m_max,wind_gusts_10m_max,wind_direction_10m_dominant,shortwave_radiation_sum,et0_fao_evapotranspiration&hourly=temperature_2m,relative_humidity_2m,dew_point_2m,apparent_temperature,precipitation,rain,snowfall,snow_depth,evapotranspiration,et0_fao_evapotranspiration,vapour_pressure_deficit,weather_code&models=meteoswiss_icon_ch2&current=temperature_2m,relative_humidity_2m,apparent_temperature,is_day,wind_speed_10m,wind_direction_10m,wind_gusts_10m,weather_code,cloud_cover,pressure_msl,surface_pressure,showers,snowfall,rain,precipitation&timezone=Europe%2FBerlin&forecast_days=7"

#define ZIP "7000" // Chur

#endif // MAIN_H