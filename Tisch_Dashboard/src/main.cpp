// // .----------------------------------------.
// // | ___            _           _           |
// // ||_ _|_ __   ___| |_   _  __| | ___  ___ |
// // | | || '_ \ / __| | | | |/ _` |/ _ \/ __||
// // | | || | | | (__| | |_| | (_| |  __/\__ \|
// // ||___|_| |_|\___|_|\__,_|\__,_|\___||___/|
// // '----------------------------------------'

// #include "main.h"
#include <Arduino.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

// // .--------------------------------------------------------------------------.
// // |  ____ _       _           _  __     __         _       _     _           |
// // | / ___| | ___ | |__   __ _| | \ \   / /_ _ _ __(_) __ _| |__ | | ___  ___ |
// // || |  _| |/ _ \| '_ \ / _` | |  \ \ / / _` | '__| |/ _` | '_ \| |/ _ \/ __||
// // || |_| | | (_) | |_) | (_| | |   \ V / (_| | |  | | (_| | |_) | |  __/\__ \|
// // | \____|_|\___/|_.__/ \__,_|_|    \_/ \__,_|_|  |_|\__,_|_.__/|_|\___||___/|
// // '--------------------------------------------------------------------------'

// // .----------------------------------------------------.
// // | _____                 _   _                        |
// // ||  ___|   _ _ __   ___| |_(_) ___  _ __             |
// // || |_ | | | | '_ \ / __| __| |/ _ \| '_ \            |
// // ||  _|| |_| | | | | (__| |_| | (_) | | | |           |
// // ||_|__ \__,_|_| |_|\___|\__|_|\___/|_| |_|           |
// // ||  _ \ _ __ ___ | |_ ___ | |_ _   _ _ __   ___  ___ |
// // || |_) | '__/ _ \| __/ _ \| __| | | | '_ \ / _ \/ __||
// // ||  __/| | | (_) | || (_) | |_| |_| | |_) |  __/\__ \|
// // ||_|   |_|  \___/ \__\___/ \__|\__, | .__/ \___||___/|
// // |                              |___/|_|              |
// // '----------------------------------------------------'

// // .----------------------------.
// // | ____       _               |
// // |/ ___|  ___| |_ _   _ _ __  |
// // |\___ \ / _ \ __| | | | '_ \ |
// // | ___) |  __/ |_| |_| | |_) ||
// // ||____/ \___|\__|\__,_| .__/ |
// // |                     |_|    |
// // '----------------------------'

// void setup()
// {
//   Serial.begin(115200);
//   Serial.println("Setup started");

//   WiFi.begin(ssid, password);
//   Serial.println("Connecting");
//   while (WiFi.status() != WL_CONNECTED)
//   {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("");
//   Serial.print("Connected to WiFi network with IP Address: ");
//   Serial.println(WiFi.localIP());

//   Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");

//   Serial.println("Setup ended");
// }

// // .------------------------.
// // | _                      |
// // || |    ___   ___  _ __  |
// // || |   / _ \ / _ \| '_ \ |
// // || |__| (_) | (_) | |_) ||
// // ||_____\___/ \___/| .__/ |
// // |                 |_|    |
// // '------------------------'

// String weatherVersionApi_buffer;
// String weatherForecastApi_buffer;

// void loop()
// {

//   if (WiFi.status() == WL_CONNECTED)
//   {

//     // weatherVersionApi_buffer = httpGETRequest(WEATER_API_VERSIONS);
//     weatherVersionApi_buffer = httpGETRequest(OPEN_METEO_WEATHER_API_URL);
//     // Serial.println(jsonBuffer);
//     JSONVar versionData_JSON = JSON.parse(weatherVersionApi_buffer);

//     if (JSON.typeof(versionData_JSON) == "undefined")
//     {
//       Serial.println("Parsing input failed!");
//       return;
//     }
//     Serial.print("Weather Code: ");
//     Serial.print(versionData_JSON["current"]["weather_code"]);
//     Serial.println("");

//     Serial.print("Temperature ");
//     Serial.print(versionData_JSON["current"]["temperature_2m"]);
//     Serial.println("°C");
//   }
//   else
//   {
//     Serial.println("WiFi Disconnected");
//   }

//   delay(10000); // alle 10 Sekunden
// }

// // Beispiel: Touch an GPIO4 (T0)
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

  static uint8_t old_minutes = rtc_getMinutes();
  static uint8_t new_minutes = rtc_getMinutes();

  new_minutes = rtc_getMinutes();
  if (old_minutes != new_minutes)
  {
    old_minutes = new_minutes;
    Serial.println("Update Display");
    // displayManager_refreshDisplay();
    displayManager_updateDisplay();
    Serial.println("Update Done");
  }

  delay(500);
}
