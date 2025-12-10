// .----------------------------------------.
// | ___            _           _           |
// ||_ _|_ __   ___| |_   _  __| | ___  ___ |
// | | || '_ \ / __| | | | |/ _` |/ _ \/ __||
// | | || | | | (__| | |_| | (_| |  __/\__ \|
// ||___|_| |_|\___|_|\__,_|\__,_|\___||___/|
// '----------------------------------------'

#include "DisplayManager.h"
#include <stdio.h>

// .----------------------------------.
// | ____        __ _                 |
// ||  _ \  ___ / _(_)_ __   ___  ___ |
// || | | |/ _ \ |_| | '_ \ / _ \/ __||
// || |_| |  __/  _| | | | |  __/\__ \|
// ||____/ \___|_| |_|_| |_|\___||___/|
// '----------------------------------'

static uint8_t weatherPage[(EPD_7IN5_V2_WIDTH / 8) * EPD_7IN5_V2_HEIGHT];

uint8_t dateTextCharCounter = 0;

// Outline frame definitions ------------------------------------------------
#define TEMP_FRAME_START_X 0
#define TEMP_FRAME_START_Y 0
#define TEMP_FRAME_END_X (TEMP_POSITION_X + (TEMP_FONT.Width * 6) + 5)
#define TEMP_FRAME_END_Y (TEMP_HOUSE_ICON_Y + houseFilled_24x24_height + 5)

#define DATE_AND_TIME_FRAME_START_X 0
#define DATE_AND_TIME_FRAME_Y (DATE_POSITION_Y + DATE_FONT.Height + 20)
#define DATE_AND_TIME_FRAME_END_X EPD_7IN5_V2_WIDTH

#define DATE_AND_TIME_FRAME_START_Y 0
#define DATE_AND_TIME_FRAME_END_Y DATE_AND_TIME_FRAME_Y
#define DATE_AND_TIME_FRAME_X ((EPD_7IN5_V2_WIDTH + 40) / 2)

#define TODAYS_WEATHER_FRAME_X ((EPD_7IN5_V2_WIDTH * 11) / 20)
#define TODAYS_WEATHER_FRAME_START_Y DATE_AND_TIME_FRAME_Y
#define TODAYS_WEATHER_FRAME_END_Y (EPD_7IN5_V2_HEIGHT)

#define WEATHER_ONE_DAY_FRAME_X (((EPD_7IN5_V2_WIDTH - TODAYS_WEATHER_FRAME_X) / 2) + TODAYS_WEATHER_FRAME_X)
#define WEATHER_ONE_DAY_FRAME_START_Y DATE_AND_TIME_FRAME_Y
#define WEATHER_ONE_DAY_FRAME_END_Y (EPD_7IN5_V2_HEIGHT)

#define WEATHER_TWO_DAY_FRAME_X ((((EPD_7IN5_V2_WIDTH - TODAYS_WEATHER_FRAME_X) * 2) / 3) + TODAYS_WEATHER_FRAME_X)
#define WEATHER_TWO_DAY_FRAME_START_Y DATE_AND_TIME_FRAME_Y
#define WEATHER_TWO_DAY_FRAME_END_Y (EPD_7IN5_V2_HEIGHT)

#define WEATHER_DAY_ONE_HORIZONTAL_FRAME_START_X (TODAYS_WEATHER_FRAME_X)
#define WEATHER_DAY_ONE_HORIZONTAL_FRAME_END_X (EPD_7IN5_V2_WIDTH)
#define WEATHER_DAY_ONE_HORIZONTAL_FRAME_Y (((EPD_7IN5_V2_HEIGHT - WEATHER_ONE_DAY_FRAME_START_Y) * 1) / 3) + WEATHER_ONE_DAY_FRAME_START_Y

#define WEATHER_DAY_TWO_HORIZONTAL_FRAME_START_X (TODAYS_WEATHER_FRAME_X)
#define WEATHER_DAY_TWO_HORIZONTAL_FRAME_END_X (EPD_7IN5_V2_WIDTH)
#define WEATHER_DAY_TWO_HORIZONTAL_FRAME_Y (((EPD_7IN5_V2_HEIGHT - WEATHER_ONE_DAY_FRAME_START_Y) * 2) / 3) + WEATHER_ONE_DAY_FRAME_START_Y

// Temperature and date/time text definitions --------------------------------
#define TEMP_HOUSE_ICON_X 10 // (DATE_POSITION_X + (TEMP_FONT.Width * 6) + 5)
#define TEMP_POSITION_X (TEMP_HOUSE_ICON_X + houseFilled_24x24_width + 5)
#define TEMP_HOUSE_ICON_Y 2
#define TEMP_POSITION_Y (TEMP_HOUSE_ICON_Y + 3)
#define TEMP_FONT OrbitronRegular20

#define TIME_POSITON_X ((DATE_AND_TIME_FRAME_X - (TIME_FONT.Width * 5)) / 2)
#define TIME_POSITON_Y TEMP_FRAME_END_Y + 10
#define TIME_FONT OrbitronBold70

#define DATE_POSITION_X ((DATE_AND_TIME_FRAME_X - (DATE_FONT.Width * dateTextCharCounter)) / 2)
#define DATE_POSITION_Y (TIME_POSITON_Y + OrbitronBold70.Height + 10)
#define DATE_FONT OrbitronBold22

// Todays weather position definitions ---------------------------------------
#define TODAYS_WEATHER_TITLE_X ((TODAYS_WEATHER_FRAME_X) / 20)
#define TODAYS_WEATHER_TITLE_Y (DATE_AND_TIME_FRAME_Y + 10)
#define TODAYS_WEATHER_TITLE_FONT OrbitronBold25

#define TODAYS_WEATHER_TITLE_UNDERLINE_X_START TODAYS_WEATHER_TITLE_X
#define TODAYS_WEATHER_TITLE_UNDERLINE_X_END (TODAYS_WEATHER_TITLE_X + (TODAYS_WEATHER_TITLE_FONT.Width * 5) + 10)
#define TODAYS_WEATHER_TITLE_UNDERLINE_Y (TODAYS_WEATHER_TITLE_Y + TODAYS_WEATHER_TITLE_FONT.Height)

#define TODAYS_WEATHER_NOW_X TODAYS_WEATHER_TITLE_X
#define TODAYS_WEATHER_NOW_Y (TODAYS_WEATHER_TITLE_Y + TODAYS_WEATHER_TITLE_FONT.Height + 10)
#define TODAYS_WEATHER_NOW_FONT OrbitronBold20

#define NOW_TEMP_POSITION_X (TODAYS_WEATHER_NOW_X + TODAYS_WEATHER_NOW_FONT.Height)
#define NOW_TEMP_POSITION_Y (TODAYS_WEATHER_NOW_Y + TODAYS_WEATHER_NOW_FONT.Height + 5)
#define NOW_TEMP_FONT OrbitronBold22

// .---------------------------------------------.
// | _____                 _   _                 |
// ||  ___|   _ _ __   ___| |_(_) ___  _ __  ___ |
// || |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __||
// ||  _|| |_| | | | | (__| |_| | (_) | | | \__ \|
// ||_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/|
// '---------------------------------------------'

void displayManager_drawBoxOutlines()
{
    Paint_SelectImage(weatherPage);
    // Outline horizontal line through the middle
    Paint_DrawLine(DATE_AND_TIME_FRAME_START_X, DATE_AND_TIME_FRAME_Y, DATE_AND_TIME_FRAME_END_X, DATE_AND_TIME_FRAME_Y, BLACK, DOT_PIXEL_3X3, LINE_STYLE_SOLID);
    // Outline vertical line through the middle
    Paint_DrawLine(DATE_AND_TIME_FRAME_X, DATE_AND_TIME_FRAME_START_Y, DATE_AND_TIME_FRAME_X, DATE_AND_TIME_FRAME_END_Y, BLACK, DOT_PIXEL_3X3, LINE_STYLE_SOLID);

    // Outline for todays weather
    Paint_DrawLine(TODAYS_WEATHER_FRAME_X, TODAYS_WEATHER_FRAME_START_Y, TODAYS_WEATHER_FRAME_X, TODAYS_WEATHER_FRAME_END_Y, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

    // ----------------------------------------------------------------------------------------------------
    // Use two vertical lines for the weather day 1-3 instead
    // ----------------------------------------------------------------------------------------------------
    // Outline for weather day 1
    // Paint_DrawLine(WEATHER_ONE_DAY_FRAME_X, WEATHER_ONE_DAY_FRAME_START_Y, WEATHER_ONE_DAY_FRAME_X, WEATHER_ONE_DAY_FRAME_END_Y, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
    // Outline for weather day 2
    // Paint_DrawLine(WEATHER_TWO_DAY_FRAME_X, WEATHER_TWO_DAY_FRAME_START_Y, WEATHER_TWO_DAY_FRAME_X, WEATHER_TWO_DAY_FRAME_END_Y, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

    // ----------------------------------------------------------------------------------------------------
    // Use two horizontal lines for the weather day 1-3 instead
    // ----------------------------------------------------------------------------------------------------
    // First out of two lines
    Paint_DrawLine(WEATHER_DAY_ONE_HORIZONTAL_FRAME_START_X, WEATHER_DAY_ONE_HORIZONTAL_FRAME_Y, WEATHER_DAY_ONE_HORIZONTAL_FRAME_END_X, WEATHER_DAY_ONE_HORIZONTAL_FRAME_Y, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    // Second out of two lines
    Paint_DrawLine(WEATHER_DAY_TWO_HORIZONTAL_FRAME_START_X, WEATHER_DAY_TWO_HORIZONTAL_FRAME_Y, WEATHER_DAY_TWO_HORIZONTAL_FRAME_END_X, WEATHER_DAY_TWO_HORIZONTAL_FRAME_Y, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
}

void displayManager_generateTimeAndDateText()
{
    Paint_SelectImage(weatherPage);
    char timeText[6];
    sprintf(timeText, "%02d:%02d", rtc_getHour(), rtc_getMinutes());
    Paint_DrawString_EN(TIME_POSITON_X, TIME_POSITON_Y, timeText, &TIME_FONT, WHITE, BLACK);

    char dateText[25];
    sprintf(dateText, "%s,%02d.%02d.%04d", rtc_getWeekday(), rtc_getDay(), rtc_getMonth(), rtc_getYear());

    for (uint8_t i = 0; i < sizeof(dateText); i++)
    {
        if (dateText[i] == '\0')
        {
            dateTextCharCounter = i;
            break;
        }
        else
        {
            dateTextCharCounter = sizeof(dateText);
        }
    }

    Paint_DrawString_EN(DATE_POSITION_X, DATE_POSITION_Y, dateText, &DATE_FONT, WHITE, BLACK);
}

void displayManager_generateHomeTemperature()
{
    Paint_SelectImage(weatherPage);
    // Outline horizontal line
    Paint_DrawLine(TEMP_FRAME_START_X, TEMP_FRAME_END_Y, TEMP_FRAME_END_X, TEMP_FRAME_END_Y, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    // Outline vertical line
    Paint_DrawLine(TEMP_FRAME_END_X, TEMP_FRAME_START_Y, TEMP_FRAME_END_X, TEMP_FRAME_END_Y, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

    // Text
    char tempText[9];
    sprintf(tempText, "%.1f", tempSensor_getTemperature());
    for (int i = 0; i < sizeof(tempText); i++)
    {
        if (tempText[i] == '\0')
        {
            tempText[i] = DEGREE_CHAR;
            tempText[i + 1] = 'C';
            tempText[i + 2] = '\0';
            break;
        }
    }
    Paint_DrawString_EN(TEMP_POSITION_X, TEMP_POSITION_Y, tempText, &TEMP_FONT, WHITE, BLACK);
    Paint_DrawLine(TEMP_FRAME_END_X, TEMP_FRAME_START_Y, TEMP_FRAME_END_X, TEMP_FRAME_END_Y, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

    Paint_DrawImage(houseFilled_24x24_bits, TEMP_HOUSE_ICON_X, TEMP_HOUSE_ICON_Y, houseFilled_24x24_width, houseFilled_24x24_height);
}

void displayManager_generateTodaysWeather()
{
    Paint_SelectImage(weatherPage);

    // Heute Titel mit underline
    char todayTitleText[] = "Heute";
    Paint_DrawString_EN(TODAYS_WEATHER_TITLE_X, TODAYS_WEATHER_TITLE_Y, todayTitleText, &TODAYS_WEATHER_TITLE_FONT, WHITE, BLACK);
    Paint_DrawLine(TODAYS_WEATHER_TITLE_UNDERLINE_X_START, TODAYS_WEATHER_TITLE_UNDERLINE_Y, TODAYS_WEATHER_TITLE_UNDERLINE_X_END, TODAYS_WEATHER_TITLE_UNDERLINE_Y, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

    // Jetzt Text
    char todayNowText[] = "Jetzt";
    Paint_DrawString_EN(TODAYS_WEATHER_NOW_X, TODAYS_WEATHER_NOW_Y, todayNowText, &TODAYS_WEATHER_NOW_FONT, WHITE, BLACK);

    // Temperatur jetzt
    char tempNowText[9];

    sprintf(tempNowText, "%.1f", weatherAPI_getCurrentTemperature());
    for (int i = 0; i < sizeof(tempNowText); i++)
    {
        if (tempNowText[i] == '\0')
        {
            tempNowText[i] = DEGREE_CHAR;
            tempNowText[i + 1] = 'C';
            tempNowText[i + 2] = '\0';
            break;
        }
    }

    Paint_DrawString_EN(NOW_TEMP_POSITION_X, NOW_TEMP_POSITION_Y, tempNowText, &NOW_TEMP_FONT, WHITE, BLACK);
}

void displayManager_init()
{

    // Hardware + Display initialize
    DEV_Module_Init();   // Init Hardware function
    EPD_7IN5_V2_Init();  // Init Display function
    EPD_7IN5_V2_Clear(); // clear Display
    DEV_Delay_ms(500);   // 0.5 second delay

    // Initialize the weather page
    Paint_NewImage(weatherPage, EPD_7IN5_V2_WIDTH, EPD_7IN5_V2_HEIGHT, 0, WHITE);
    Paint_SelectImage(weatherPage);
    Paint_Clear(WHITE);

    displayManager_updateDisplay();

    //   Display weather page
    // EPD_7IN5_V2_Display(weatherPage);
    // DEV_Delay_ms(8000); // 8 Sekunden warten

    // Anzeigen
    // Paint_SelectImage(weatherPage);
    // Paint_DrawImage(houseFilled_24x24_bits, 10, 10, houseFilled_24x24_width, houseFilled_24x24_height);
    // EPD_7IN5_V2_Display(weatherPage);
    // DEV_Delay_ms(8000); // 8 Sekunden warten

    // for (int i = 0; i < 5; i++)
    // {
    //     EPD_7IN5_V2_Clear(); // komplett weiß
    //     DEV_Delay_ms(2000);
    // }

    // sleep
    // free(weatherPage);
    // EPD_7IN5_V2_Sleep();
}

void displayManager_updateDisplay()
{
    EPD_7IN5_V2_Init();
    EPD_7IN5_V2_ClearBlack();
    delay(1000);
    EPD_7IN5_V2_Clear();
    delay(1000);
    // EPD_7IN5_V2_Init();

    Paint_Clear(WHITE);
    displayManager_generateTimeAndDateText();
    displayManager_generateHomeTemperature();
    displayManager_generateTodaysWeather();

    displayManager_drawBoxOutlines();

    EPD_7IN5_V2_Display(weatherPage);
    // free(weatherPage); // generates an unkonwn error here --> to be investigated
    EPD_7IN5_V2_Sleep();
}

void displayManager_refreshDisplay()
{
    EPD_7IN5_V2_Init();
    EPD_7IN5_V2_Clear();
    EPD_7IN5_V2_Sleep();
}