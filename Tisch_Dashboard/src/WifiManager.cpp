// .----------------------------------------.
// | ___            _           _           |
// ||_ _|_ __   ___| |_   _  __| | ___  ___ |
// | | || '_ \ / __| | | | |/ _` |/ _ \/ __||
// | | || | | | (__| | |_| | (_| |  __/\__ \|
// ||___|_| |_|\___|_|\__,_|\__,_|\___||___/|
// '----------------------------------------'

#include "WifiManager.h"

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

const char *ssid = "brz-63878";
const char *password = "eqao-25ds-iry4-8imk";

// .---------------------------------------------.
// | _____                 _   _                 |
// ||  ___|   _ _ __   ___| |_(_) ___  _ __  ___ |
// || |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __||
// ||  _|| |_| | | | | (__| |_| | (_) | | | \__ \|
// ||_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/|
// '---------------------------------------------'

void wifiManager_init()
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
}


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
  //   WiFiClient client;
  // HTTPClient http;
    
  // // Your Domain name with URL path or IP address with path
  // http.begin(client, serverName);
  
  // // If you need Node-RED/server authentication, insert user and password below
  // //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
  
  // // Send HTTP POST request
  // int httpResponseCode = http.GET();
  
  // String payload = "{}"; 
  
  // if (httpResponseCode>0) {
  //   Serial.print("HTTP Response code: ");
  //   Serial.println(httpResponseCode);
  //   payload = http.getString();
  // }
  // else {
  //   Serial.print("Error code: ");
  //   Serial.println(httpResponseCode);
  // }
  // // Free resources
  // http.end();

  // return payload;
}
