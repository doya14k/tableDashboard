// // .----------------------------------------.
// // | ___            _           _           |
// // ||_ _|_ __   ___| |_   _  __| | ___  ___ |
// // | | || '_ \ / __| | | | |/ _` |/ _ \/ __||
// // | | || | | | (__| | |_| | (_| |  __/\__ \|
// // ||___|_| |_|\___|_|\__,_|\__,_|\___||___/|
// // '----------------------------------------'

// #include "main.h"
// #include <Arduino.h>

// #include <WiFi.h>
// #include <HTTPClient.h>
// #include <Arduino_JSON.h>

// .--------------------------------------------------------------------------.
// |  ____ _       _           _  __     __         _       _     _           |
// | / ___| | ___ | |__   __ _| | \ \   / /_ _ _ __(_) __ _| |__ | | ___  ___ |
// || |  _| |/ _ \| '_ \ / _` | |  \ \ / / _` | '__| |/ _` | '_ \| |/ _ \/ __||
// || |_| | | (_) | |_) | (_| | |   \ V / (_| | |  | | (_| | |_) | |  __/\__ \|
// | \____|_|\___/|_.__/ \__,_|_|    \_/ \__,_|_|  |_|\__,_|_.__/|_|\___||___/|
// '--------------------------------------------------------------------------'

// .----------------------------------------------------.
// | _____                 _   _                        |
// ||  ___|   _ _ __   ___| |_(_) ___  _ __             |
// || |_ | | | | '_ \ / __| __| |/ _ \| '_ \            |
// ||  _|| |_| | | | | (__| |_| | (_) | | | |           |
// ||_|__ \__,_|_| |_|\___|\__|_|\___/|_| |_|           |
// ||  _ \ _ __ ___ | |_ ___ | |_ _   _ _ __   ___  ___ |
// || |_) | '__/ _ \| __/ _ \| __| | | | '_ \ / _ \/ __||
// ||  __/| | | (_) | || (_) | |_| |_| | |_) |  __/\__ \|
// ||_|   |_|  \___/ \__\___/ \__|\__, | .__/ \___||___/|
// |                              |___/|_|              |
// '----------------------------------------------------'

// .----------------------------.
// | ____       _               |
// |/ ___|  ___| |_ _   _ _ __  |
// |\___ \ / _ \ __| | | | '_ \ |
// | ___) |  __/ |_| |_| | |_) ||
// ||____/ \___|\__|\__,_| .__/ |
// |                     |_|    |
// '----------------------------'

// void setup()
// {
//   Serial.begin(115200);
//   Serial.println("Setup started");

//   wifiManager_init();
//   // WiFi.begin("brz-63878", "eqao-25ds-iry4-8imk");
//   // Serial.println("Connecting");
//   // while (WiFi.status() != WL_CONNECTED)
//   // {
//   //   delay(500);
//   //   Serial.print(".");
//   // }
//   // Serial.println("");
//   // Serial.print("Connected to WiFi network with IP Address: ");
//   // Serial.println(WiFi.localIP());

//   // Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");

//   Serial.println("Setup ended");
// }

// .------------------------.
// | _                      |
// || |    ___   ___  _ __  |
// || |   / _ \ / _ \| '_ \ |
// || |__| (_) | (_) | |_) ||
// ||_____\___/ \___/| .__/ |
// |                 |_|    |
// '------------------------'

// String weatherVersionApi_buffer;
// String weatherForecastApi_buffer;

// void loop()
// {

//   weatherAPI_updateWeatherData();
//   weatherAPI_getCurrentTemperature();

//   // if (WiFi.status() == WL_CONNECTED)
//   // {

//   //   // weatherVersionApi_buffer = httpGETRequest(WEATER_API_VERSIONS);
//   //   weatherVersionApi_buffer = httpGETRequest("https://api.open-meteo.com/v1/forecast?latitude=46.8499&longitude=9.5329&daily=weather_code,temperature_2m_max,apparent_temperature_max,temperature_2m_min,apparent_temperature_min,sunshine_duration,sunset,sunrise,daylight_duration,rain_sum,showers_sum,snowfall_sum,precipitation_hours,precipitation_sum,precipitation_probability_max,wind_speed_10m_max,wind_gusts_10m_max,wind_direction_10m_dominant,shortwave_radiation_sum,et0_fao_evapotranspiration&hourly=temperature_2m,relative_humidity_2m,dew_point_2m,apparent_temperature,precipitation,rain,snowfall,snow_depth,evapotranspiration,et0_fao_evapotranspiration,vapour_pressure_deficit,weather_code&models=meteoswiss_icon_ch2&current=temperature_2m,relative_humidity_2m,apparent_temperature,is_day,wind_speed_10m,wind_direction_10m,wind_gusts_10m,weather_code,cloud_cover,pressure_msl,surface_pressure,showers,snowfall,rain,precipitation&timezone=Europe%2FBerlin&forecast_days=7");
//   //   // Serial.println(jsonBuffer);
//   //   JSONVar versionData_JSON = JSON.parse(weatherVersionApi_buffer);

//   //   if (JSON.typeof(versionData_JSON) == "undefined")
//   //   {
//   //     Serial.println("Parsing input failed!");
//   //     return;
//   //   }
//   //   Serial.print("Weather Code: ");
//   //   Serial.print(versionData_JSON["current"]["weather_code"]);
//   //   Serial.println("");

//   //   Serial.print("Temperature ");
//   //   Serial.print(versionData_JSON["current"]["temperature_2m"]);
//   //   Serial.println("°C");
//   // }
//   // else
//   // {
//   //   Serial.println("WiFi Disconnected");
//   // }

//   delay(10000); // alle 10 Sekunden
// }

// Beispiel: Touch an GPIO4 (T0)
// #define TOUCH_PIN T0  // alternativ: 4

// void setup() {
//   Serial.begin(9600);
//   delay(1000);
//   Serial.println("Kapazitive Gestenerkennung gestartet!");
// }

// void loop() {
//   int touchValue = touchRead(TOUCH_PIN);
//   Serial.println(touchValue);

//   if(touchValue < 30) { // Schwellwert anpassen!
//     Serial.println("Berührung erkannt!");
//   }

//   delay(100);
// }

// Display example code -----------------------------------------------------------------------------------------------------------------------

#include <stdlib.h>
#include "main.h"

void setup()
{
  // Serial Monitor initialize
  Serial.begin(115200);
  Serial.println("Start Setup");

  Serial.println("WifiManagerInit started");
  // Wifi initialize
  wifiManager_init();
  Serial.println("WifiManagerInit done");

  Serial.println("TempSensorInit started");
  // TempSensor initialize
  tempSensor_init();
  Serial.println("TempSensorInit done");

  Serial.println("RTCInit started");
  // RTC initialize
  rtc_init();
  Serial.println("RTCInit done");

  Serial.println("WeatherAPIInit started");
  // Weather API initialize
  weatherAPI_init();
  Serial.println("WeatherAPIInit done");

  Serial.println("DisplayManagerInit started");
  // Display initialize
  displayManager_init();
  Serial.println("DisplayManagerInit done");

  Serial.println("Setup done");
}

void loop()
{
  Serial.print("Temp ");
  Serial.print(tempSensor_getTemperature());
  Serial.println("°C");
  rtc_updateTime();
  rtc_printTime();
  // timeAPI_updateTime();
  // timeAPI_printTime();

  static uint8_t old_minutes = rtc_getMinutes();
  static uint8_t new_minutes = rtc_getMinutes();

  new_minutes = rtc_getMinutes();
  if (old_minutes != new_minutes)
  {
    old_minutes = new_minutes;
    weatherAPI_updateWeatherData();
    Serial.println("Update Display");
    // displayManager_refreshDisplay();
    displayManager_updateDisplay();
    Serial.println("Update Done");
  }

  delay(500);
}
