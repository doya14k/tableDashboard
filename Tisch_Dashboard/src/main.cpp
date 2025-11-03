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

// const char *ssid = "brz-63878";
// const char *password = "eqao-25ds-iry4-8imk";
// const char *weatherApiUrl;

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

String httpGETRequest(const char *serverName)
{
  HTTPClient http;
  http.begin(serverName);
  int httpResponseCode = http.GET();
  String payload = "{}";
  if (httpResponseCode > 0)
  {
    payload = http.getString();
  }
  else
  {
    Serial.print("HTTP GET failed, error: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  return payload;
}

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

#include "DEV_Config.h"
#include "EPD.h"
#include "GUI_Paint.h"
#include "fonts.h"
#include <stdlib.h>
#include "main.h"

void setup()
{
  // Serial Monitor initialize
  Serial.begin(115200);
  Serial.println("Start Setup");

  // TempSensor initialize
  tempSensor_init();

  // RTC initialize
  rtc_init();

  // Hardware + Display initialize
  // DEV_Module_Init();
  // EPD_7IN5_V2_Init();
  // EPD_7IN5_V2_Clear();
  // DEV_Delay_ms(500);

  // // Picture Storage reserve
  // UBYTE *BlackImage;
  // UWORD Imagesize = ((EPD_7IN5_V2_WIDTH % 8 == 0) ? (EPD_7IN5_V2_WIDTH / 8) : (EPD_7IN5_V2_WIDTH / 8 + 1)) * EPD_7IN5_V2_HEIGHT;
  // BlackImage = (UBYTE *)malloc(Imagesize);
  // if (BlackImage == NULL)
  // {
  //   Serial.println("Memory alloc failed!");
  //   while (1)
  //     ;
  // }

  // // Neues Bild erzeugen & weiß füllen
  // Paint_NewImage(BlackImage, EPD_7IN5_V2_WIDTH, EPD_7IN5_V2_HEIGHT, 0, WHITE);
  // Paint_SelectImage(BlackImage);
  // Paint_Clear(WHITE);

  // Text in der Mitte platzieren
  // const char message[] = "23:59 12" "\x7F" "C";
  //   int textX = (EPD_7IN5_V2_WIDTH - (strlen(message) * OrbitronRegular20.Width)) / 2;
  //   int textY = (EPD_7IN5_V2_HEIGHT - OrbitronRegular20.Height) / 2;
  //   Paint_DrawString_EN(textX, textY, message, &OrbitronRegular20, WHITE, BLACK);

  //   // Anzeigen
  //   EPD_7IN5_V2_Display(BlackImage);
  //   DEV_Delay_ms(8000); // 8 Sekunden warten

  // Anzeigen
  // Paint_SelectImage(BlackImage);
  // Paint_DrawImage(houseFi888lled_40x40_bits, 10, 10, houseFilled_40x40_width, houseFilled_40x40_height);
  // EPD_7IN5_V2_Display(BlackImage);
  // DEV_Delay_ms(8000); // 8 Sekunden warten

  // for (int i = 0; i < 5; i++)
  // {
  //   EPD_7IN5_V2_Clear(); // komplett weiß
  //   DEV_Delay_ms(2000);
  // }

  // Speicher freigeben und schlafen legen
  // free(BlackImage);
  // EPD_7IN5_V2_Sleep();

  Serial.println("Setup done");
}

void loop()
{
  Serial.print("Temp ");
  Serial.print(tempSensor_getTemperature());
  Serial.println("°C");
  rtc_updateTime();
  rtc_printTime();

  Serial.println(rtc_getWeekday());

  delay(500);
}
