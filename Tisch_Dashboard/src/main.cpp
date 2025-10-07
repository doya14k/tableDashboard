// .----------------------------------------.
// | ___            _           _           |
// ||_ _|_ __   ___| |_   _  __| | ___  ___ |
// | | || '_ \ / __| | | | |/ _` |/ _ \/ __||
// | | || | | | (__| | |_| | (_| |  __/\__ \|
// ||___|_| |_|\___|_|\__,_|\__,_|\___||___/|
// '----------------------------------------'

#include "main.h"
#include <Arduino.h>


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

void setup()
{
  Serial.begin(115200);
  Serial.println("Setup gestartet");
}


// .------------------------.
// | _                      |
// || |    ___   ___  _ __  |
// || |   / _ \ / _ \| '_ \ |
// || |__| (_) | (_) | |_) ||
// ||_____\___/ \___/| .__/ |
// |                 |_|    |
// '------------------------'

void loop()
{
  Serial.println("Loop läuft...");
  delay(2000);
}

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

// #include "DEV_Config.h"
// #include "EPD.h"
// #include "GUI_Paint.h"
// #include "fonts.h"
// #include <stdlib.h>

// void setup()
// {
//   Serial.begin(115200);
//   Serial.println("Hello World Demo");

//   // Hardware + Display initialisieren
//   DEV_Module_Init();
//   EPD_7IN5_V2_Init();
//   EPD_7IN5_V2_Clear();
//   DEV_Delay_ms(500);

//   // Bildspeicher reservieren
//   UBYTE *BlackImage;
//   UWORD Imagesize = ((EPD_7IN5_V2_WIDTH % 8 == 0) ? (EPD_7IN5_V2_WIDTH / 8) : (EPD_7IN5_V2_WIDTH / 8 + 1)) * EPD_7IN5_V2_HEIGHT;
//   BlackImage = (UBYTE *)malloc(Imagesize);
//   if (BlackImage == NULL)
//   {
//     Serial.println("Memory alloc failed!");
//     while (1)
//       ;
//   }

//   // Neues Bild erzeugen & weiß füllen
//   Paint_NewImage(BlackImage, EPD_7IN5_V2_WIDTH, EPD_7IN5_V2_HEIGHT, 0, WHITE);
//   Paint_SelectImage(BlackImage);
//   Paint_Clear(WHITE);

//   // Text in der Mitte platzieren
//   const char *message = "HELLO DOMINIC";
//   int textX = (EPD_7IN5_V2_WIDTH - (strlen(message) * Font24.Width)) / 2;
//   int textY = (EPD_7IN5_V2_HEIGHT - Font24.Height) / 2;
//   Paint_DrawString_EN(textX, textY, message, &Font24, WHITE, BLACK);

//   // Anzeigen
//   EPD_7IN5_V2_Display(BlackImage);
//   DEV_Delay_ms(5000); // 5 Sekunden warten

//   for (int i = 0; i < 5; i++)
//   {
//     EPD_7IN5_V2_Clear(); // komplett weiß
//     DEV_Delay_ms(2000);
//   }

//   // Speicher freigeben und schlafen legen
//   free(BlackImage);
//   EPD_7IN5_V2_Sleep();
// }

// void loop()
// {
//   // nichts mehr
// }
