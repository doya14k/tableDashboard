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

// Weather API related definitions ----------------------------------------------
#define TODAY_TIME_INDEX 0
#define TOMORROW_TIME_INDEX 1
#define IN_2_DAYS_TIME_INDEX 2
#define IN_3_DAYS_TIME_INDEX 3

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
#define TEMP_POSITION_X ((TEMP_HOUSE_ICON_X + houseFilled_24x24_width + 5))
#define TEMP_HOUSE_ICON_Y 2
#define TEMP_POSITION_Y (TEMP_HOUSE_ICON_Y + 3)
#define TEMP_FONT OrbitronRegular20

#define TIME_POSITON_X ((DATE_AND_TIME_FRAME_X - (timeTextWidth)) / 2)
#define TIME_POSITON_Y TEMP_FRAME_END_Y + 10
#define TIME_FONT OrbitronBold70

#define DATE_POSITION_X ((DATE_AND_TIME_FRAME_X - (dateTextWidth)) / 2)
#define DATE_POSITION_Y (TIME_POSITON_Y + OrbitronBold70.Height + 10)
#define DATE_FONT OrbitronBold22

// Todays weather position definitions ---------------------------------------
#define TODAYS_WEATHER_TITLE_X ((TODAYS_WEATHER_FRAME_X) / 20)
#define TODAYS_WEATHER_TITLE_Y (DATE_AND_TIME_FRAME_Y + 10)
#define TODAYS_WEATHER_TITLE_FONT OrbitronBold25

#define TODAYS_WEATHER_TITLE_UNDERLINE_X_START TODAYS_WEATHER_TITLE_X
#define TODAYS_WEATHER_TITLE_UNDERLINE_X_END (TODAYS_WEATHER_TITLE_X + (todayTitleTextWidth) + 10)
#define TODAYS_WEATHER_TITLE_UNDERLINE_Y (TODAYS_WEATHER_TITLE_Y + TODAYS_WEATHER_TITLE_FONT.Height)

#define TODAYS_WEATHER_NOW_X TODAYS_WEATHER_TITLE_X
#define TODAYS_WEATHER_NOW_Y (TODAYS_WEATHER_TITLE_Y + TODAYS_WEATHER_TITLE_FONT.Height + 10)
#define TODAYS_WEATHER_NOW_FONT OrbitronBold20

#define NOW_TEMP_POSITION_X (TODAYS_WEATHER_NOW_X)
#define NOW_TEMP_POSITION_Y (TODAYS_WEATHER_NOW_Y + TODAYS_WEATHER_NOW_FONT.Height + 5)
#define NOW_TEMP_FONT OrbitronBold22

#define NOW_APPARENT_TEMP_POSITION_X (NOW_TEMP_POSITION_X)
#define NOW_APPARENT_TEMP_POSITION_Y (NOW_TEMP_POSITION_Y + NOW_TEMP_FONT.Height + 5)
#define NOW_APPARENT_TEMP_FONT OrbitronBold16

#define TODAY_SUNRISE_ICON_POSITION_X NOW_APPARENT_TEMP_POSITION_X
#define TODAY_SUNRISE_ICON_POSITION_Y (NOW_APPARENT_TEMP_POSITION_Y + NOW_APPARENT_TEMP_FONT.Height + 5)
#define TODAY_SUNRISE_FONT OrbitronBold16
#define TODAY_SUNRISE_POSITION_X (TODAY_SUNRISE_ICON_POSITION_X + sunrise_24x24_width + 10)
#define TODAY_SUNRISE_POSITION_Y (TODAY_SUNRISE_ICON_POSITION_Y + ((sunrise_24x24_height - TODAY_SUNRISE_FONT.Height) / 2))

#define TODAY_SUNSET_FONT TODAY_SUNRISE_FONT
#define TODAY_SUNSET_POSITION_X (TODAY_SUNRISE_POSITION_X + sunriseTextWidth + 20)
#define TODAY_SUNSET_POSITION_Y TODAY_SUNRISE_POSITION_Y
#define TODAY_SUNSET_ICON_POSITION_X (TODAY_SUNSET_POSITION_X + sunsetTextWidth + 13)
#define TODAY_SUNSET_ICON_POSITION_Y TODAY_SUNRISE_ICON_POSITION_Y

#define TODAY_MIN_TEMP_POSITION_X TODAY_SUNRISE_ICON_POSITION_X
#define TODAY_MIN_TEMP_POSITION_Y (TODAY_SUNRISE_ICON_POSITION_Y + sunrise_24x24_height + 10)
#define TODAY_MIN_TEMP_FONT OrbitronBold16
#define TODAY_MIN_TEMP_ICON_POSITION_X (TODAY_MIN_TEMP_POSITION_X + minTempTodayTextWidth + 10)
#define TODAY_MIN_TEMP_ICON_POSITION_Y (TODAY_MIN_TEMP_POSITION_Y + ((down_arrow_16x16_height - TODAY_MIN_TEMP_FONT.Height) / 2))

#define TODAY_MAX_TEMP_ICON_POSITION_X (TODAY_MIN_TEMP_ICON_POSITION_X + down_arrow_16x16_width + 25)
#define TODAY_MAX_TEMP_ICON_POSITION_Y (TODAY_MIN_TEMP_ICON_POSITION_Y)
#define TODAY_MAX_TEMP_POSITION_X (TODAY_MAX_TEMP_ICON_POSITION_X + up_arrow_16x16_width + 10)
#define TODAY_MAX_TEMP_POSITION_Y (TODAY_MIN_TEMP_POSITION_Y)
#define TODAY_MAX_TEMP_FONT TODAY_MIN_TEMP_FONT

#define CURRENT_SNOWFALL_POSITION_X TODAY_MIN_TEMP_POSITION_X
#define CURRENT_SNOWFALL_POSITION_Y (TODAY_MIN_TEMP_POSITION_Y + TODAY_MIN_TEMP_FONT.Height + 10)
#define CURRENT_SNOWFALL_FONT OrbitronBold20

#define CURRENT_RAIN_POSITION_X TODAY_MIN_TEMP_POSITION_X
#define CURRENT_RAIN_POSITION_Y (CURRENT_SNOWFALL_POSITION_Y)
#define CURRENT_RAIN_FONT CURRENT_SNOWFALL_FONT

#define CURRENT_CLOUD_COVER_FONT OrbitronBold22
#define CURRENT_CLOUD_COVER_POSITION_X (TODAY_MIN_TEMP_POSITION_X + precipitation_Width + 25)
#define CURRENT_CLOUD_COVER_POSITION_Y (CURRENT_SNOWFALL_POSITION_Y - ((CURRENT_CLOUD_COVER_FONT.Height - CURRENT_SNOWFALL_FONT.Height) / 2))

#define CURRENT_CLOUD_COVER_ICON_POSITION_X (CURRENT_CLOUD_COVER_POSITION_X + currentCloudCover_text_Width + 10)
#define CURRENT_CLOUD_COVER_ICON_POSITION_Y (CURRENT_SNOWFALL_POSITION_Y - ((cloudCoverIcon_32x32_height - CURRENT_CLOUD_COVER_FONT.Height) / 2))

#define CURRENT_HUMIDITY_POSITON_X CURRENT_SNOWFALL_POSITION_X
#define CURRENT_HUMIDITY_POSITON_Y (CURRENT_CLOUD_COVER_POSITION_Y + cloudCoverIcon_32x32_height + 10)
#define CURRENT_HUMIDITY_FONT OrbitronBold18

#define CURRENT_WIND_SPEED_FONT OrbitronBold18
#define CURRENT_WIND_SPEED_ICON_POSITION_X (CURRENT_HUMIDITY_POSITON_X + currentRelativeHumidity_Text_width + 15)
#define CURRENT_WIND_SPEED_ICON_POSITION_Y (CURRENT_HUMIDITY_POSITON_Y + ((CURRENT_HUMIDITY_FONT.Height - north_16x16_height) / 2))

#define CURRENT_WIND_SPEED_POSITION_X (CURRENT_WIND_SPEED_ICON_POSITION_X + north_16x16_width)
#define CURRENT_WIND_SPEED_POSITION_Y (CURRENT_HUMIDITY_POSITON_Y + ((CURRENT_HUMIDITY_FONT.Height - CURRENT_WIND_SPEED_FONT.Height) / 2))

// .---------------------------------------------.
// | _____                 _   _                 |
// ||  ___|   _ _ __   ___| |_(_) ___  _ __  ___ |
// || |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __||
// ||  _|| |_| | | | | (__| |_| | (_) | | | \__ \|
// ||_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/|
// '---------------------------------------------'

// .-------------------------------------.
// |  ___        _   _ _                 |
// | / _ \ _   _| |_| (_)_ __   ___  ___ |
// || | | | | | | __| | | '_ \ / _ \/ __||
// || |_| | |_| | |_| | | | | |  __/\__ \|
// | \___/ \__,_|\__|_|_|_| |_|\___||___/|
// '-------------------------------------'

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

// .-------------------------------------------------------.
// | _____ _                   ___     ____        _       |
// ||_   _(_)_ __ ___   ___   ( _ )   |  _ \  __ _| |_ ___ |
// |  | | | | '_ ` _ \ / _ \  / _ \/\ | | | |/ _` | __/ _ \|
// |  | | | | | | | | |  __/ | (_>  < | |_| | (_| | ||  __/|
// |  |_| |_|_| |_| |_|\___|  \___/\/ |____/ \__,_|\__\___||
// '-------------------------------------------------------'

void displayManager_generateTimeAndDateText()
{
    Paint_SelectImage(weatherPage);
    char timeText[6];
    sprintf(timeText, "%02d:%02d", rtc_getHour(), rtc_getMinutes());
    uint16_t timeTextWidth = Get_DrawedStringSize_EN(timeText, &TIME_FONT);

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

    uint16_t dateTextWidth = Get_DrawedStringSize_EN(dateText, &DATE_FONT);

    Paint_DrawString_EN(DATE_POSITION_X, DATE_POSITION_Y, dateText, &DATE_FONT, WHITE, BLACK);
}

// .-------------------------------------------------------.
// | ____                         _____                    |
// ||  _ \ ___   ___  _ __ ___   |_   _|__ _ __ ___  _ __  |
// || |_) / _ \ / _ \| '_ ` _ \    | |/ _ \ '_ ` _ \| '_ \ |
// ||  _ < (_) | (_) | | | | | |   | |  __/ | | | | | |_) ||
// ||_| \_\___/ \___/|_| |_| |_|   |_|\___|_| |_| |_| .__/ |
// |                                                |_|    |
// '-------------------------------------------------------'

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

// .-----------------------------.
// | _____         _             |
// ||_   _|__   __| | __ _ _   _ |
// |  | |/ _ \ / _` |/ _` | | | ||
// |  | | (_) | (_| | (_| | |_| ||
// |  |_|\___/ \__,_|\__,_|\__, ||
// |                       |___/ |
// '-----------------------------'

void displayManager_generate_TodaysCurrentTemperature()
{
    Paint_SelectImage(weatherPage);

    // Heute Titel mit underline
    char todayTitleText[] = "Heute";
    uint16_t todayTitleTextWidth = Get_DrawedStringSize_EN(todayTitleText, &TODAYS_WEATHER_TITLE_FONT);
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

    // Gefühlte Temperatur jetzt
    char apparentTempNowText[10];
    sprintf(apparentTempNowText, "(%.1f", weatherAPI_getCurrentApparentTemperature());
    for (int i = 0; i < sizeof(apparentTempNowText); i++)
    {
        if (apparentTempNowText[i] == '\0')
        {
            apparentTempNowText[i] = DEGREE_CHAR;
            apparentTempNowText[i + 1] = 'C';
            apparentTempNowText[i + 2] = ')';
            apparentTempNowText[i + 3] = '\0';
            break;
        }
    }
    Paint_DrawString_EN(NOW_APPARENT_TEMP_POSITION_X, NOW_APPARENT_TEMP_POSITION_Y, apparentTempNowText, &NOW_APPARENT_TEMP_FONT, WHITE, BLACK);
    // Serial.println("Testing modified DrawChar function for .2 character:");
    // Paint_DrawString_EN(NOW_APPARENT_TEMP_POSITION_X, NOW_APPARENT_TEMP_POSITION_Y, ".2", &NOW_APPARENT_TEMP_FONT, WHITE, BLACK);
    // Serial.println("End of test.");
}

void displayManager_generateTodaysSunriseAndSunsetTimes()
{
    Paint_SelectImage(weatherPage);

    // Sunrise Today
    char sunriseTodayText[8];
    sprintf(sunriseTodayText, "%s", weatherAPI_getDailySunriseTime(TODAY_TIME_INDEX).c_str());
    uint16_t sunriseTextWidth = Get_DrawedStringSize_EN(sunriseTodayText, &TODAY_SUNRISE_FONT);

    Paint_DrawString_EN(TODAY_SUNRISE_POSITION_X, TODAY_SUNRISE_POSITION_Y, sunriseTodayText, &TODAY_SUNRISE_FONT, WHITE, BLACK);
    Paint_DrawImage(sunrise_24x24_bits, TODAY_SUNRISE_ICON_POSITION_X, TODAY_SUNRISE_ICON_POSITION_Y, sunrise_24x24_width, sunrise_24x24_height);

    // Sunset Today
    char sunsetTodayText[8];
    sprintf(sunsetTodayText, "%s", weatherAPI_getDailySunsetTime(TODAY_TIME_INDEX).c_str());
    uint16_t sunsetTextWidth = Get_DrawedStringSize_EN(sunsetTodayText, &TODAY_SUNSET_FONT);

    Paint_DrawString_EN(TODAY_SUNSET_POSITION_X, TODAY_SUNSET_POSITION_Y, sunsetTodayText, &TODAY_SUNSET_FONT, WHITE, BLACK);
    Paint_DrawImage(sunset_24x24_bits, TODAY_SUNSET_ICON_POSITION_X, TODAY_SUNSET_ICON_POSITION_Y, sunset_24x24_width, sunset_24x24_height);
}

void displayManager_generateTodaysMinMaxTemperatures()
{

    // Todays Min Temperature
    char minTempTodayText[8];
    sprintf(minTempTodayText, "%.1f", weatherAPI_getDailyMinTemperature(TODAY_TIME_INDEX));

    for (int i = 0; i < sizeof(minTempTodayText); i++)
    {
        if (minTempTodayText[i] == '\0')
        {
            minTempTodayText[i] = DEGREE_CHAR;
            minTempTodayText[i + 1] = 'C';
            minTempTodayText[i + 2] = '\0';
            break;
        }
    }
    uint16_t minTempTodayTextWidth = Get_DrawedStringSize_EN(minTempTodayText, &TODAY_MIN_TEMP_FONT);
    Paint_DrawString_EN(TODAY_MIN_TEMP_POSITION_X, TODAY_MIN_TEMP_POSITION_Y, minTempTodayText, &TODAY_MIN_TEMP_FONT, WHITE, BLACK);
    Paint_DrawImage(down_arrow_16x16_bits, TODAY_MIN_TEMP_ICON_POSITION_X, TODAY_MIN_TEMP_ICON_POSITION_Y, down_arrow_16x16_width, down_arrow_16x16_height);

    // Todays Max Temperature
    char maxTempTodayText[8];
    sprintf(maxTempTodayText, "%.1f", weatherAPI_getDailyMaxTemperature(TODAY_TIME_INDEX));

    for (int i = 0; i < sizeof(maxTempTodayText); i++)
    {
        if (maxTempTodayText[i] == '\0')
        {
            maxTempTodayText[i] = DEGREE_CHAR;
            maxTempTodayText[i + 1] = 'C';
            maxTempTodayText[i + 2] = '\0';
            break;
        }
    }
    Paint_DrawImage(up_arrow_16x16_bits, TODAY_MAX_TEMP_ICON_POSITION_X, TODAY_MAX_TEMP_ICON_POSITION_Y, up_arrow_16x16_width, up_arrow_16x16_height);
    uint16_t maxTempTodayTextWidth = Get_DrawedStringSize_EN(maxTempTodayText, &TODAY_MIN_TEMP_FONT);
    Paint_DrawString_EN(TODAY_MAX_TEMP_POSITION_X, TODAY_MAX_TEMP_POSITION_Y, maxTempTodayText, &TODAY_MAX_TEMP_FONT, WHITE, BLACK);
}

void displayManager_generateTodaysPrecipitation_and_CloudCover()
{
    double currentSnowfall_cm = weatherAPI_getCurrentSnowfall();

    uint16_t precipitation_Width;

    if (currentSnowfall_cm > 0)
    // if (1)
    {
        // current Snowfall
        char currentSnowfall_cm_Text[8];
        sprintf(currentSnowfall_cm_Text, "%.1f", currentSnowfall_cm);

        for (int i = 0; i < sizeof(currentSnowfall_cm_Text); i++)
        {
            if (currentSnowfall_cm_Text[i] == '\0')
            {
                currentSnowfall_cm_Text[i] = 'c';
                currentSnowfall_cm_Text[i + 1] = 'm';
                currentSnowfall_cm_Text[i + 2] = '\0';
                break;
            }
        }

        precipitation_Width = Get_DrawedStringSize_EN(currentSnowfall_cm_Text, &CURRENT_SNOWFALL_FONT);
        Paint_DrawString_EN(CURRENT_SNOWFALL_POSITION_X, CURRENT_SNOWFALL_POSITION_Y, currentSnowfall_cm_Text, &CURRENT_SNOWFALL_FONT, WHITE, BLACK);
    }
    else
    {
        // current rain
        char currentRain_mm_Text[8];
        sprintf(currentRain_mm_Text, "%.1f", currentSnowfall_cm);

        for (int i = 0; i < sizeof(currentRain_mm_Text); i++)
        {
            if (currentRain_mm_Text[i] == '\0')
            {
                currentRain_mm_Text[i] = 'm';
                currentRain_mm_Text[i + 1] = 'm';
                currentRain_mm_Text[i + 2] = '\0';
                break;
            }
        }

        precipitation_Width = Get_DrawedStringSize_EN(currentRain_mm_Text, &CURRENT_RAIN_FONT);
        Paint_DrawString_EN(CURRENT_RAIN_POSITION_X, CURRENT_RAIN_POSITION_Y, currentRain_mm_Text, &CURRENT_RAIN_FONT, WHITE, BLACK);
    }

    // Current Cloud-Cover
    char currentCloudCover_Text[8];
    sprintf(currentCloudCover_Text, "%d", weatherAPI_getCurrentCloudCover());

    for (int i = 0; i < sizeof(currentCloudCover_Text); i++)
    {
        if (currentCloudCover_Text[i] == '\0')
        {
            currentCloudCover_Text[i] = '%';
            currentCloudCover_Text[i + 1] = '\0';
            break;
        }
    }

    uint16_t currentCloudCover_text_Width = Get_DrawedStringSize_EN(currentCloudCover_Text, &CURRENT_CLOUD_COVER_FONT);
    Paint_DrawString_EN(CURRENT_CLOUD_COVER_POSITION_X, CURRENT_CLOUD_COVER_POSITION_Y, currentCloudCover_Text, &CURRENT_CLOUD_COVER_FONT, WHITE, BLACK);
    Paint_DrawImage(cloudCoverIcon_32x32_bits, CURRENT_CLOUD_COVER_ICON_POSITION_X, CURRENT_CLOUD_COVER_ICON_POSITION_Y, cloudCoverIcon_32x32_width, cloudCoverIcon_32x32_height);
}

void displayManager_generateTodaysWindAndHumidity()
{
    // Humidity
    char currentRelativeHumidity_Text[10];
    sprintf(currentRelativeHumidity_Text, "%.0f", weatherAPI_getCurrentRelativeHumidity());

    for (int i = 0; i < sizeof(currentRelativeHumidity_Text); i++)
    {
        if (currentRelativeHumidity_Text[i] == '\0')
        {
            currentRelativeHumidity_Text[i] = '%';
            currentRelativeHumidity_Text[i + 1] = 'R';
            currentRelativeHumidity_Text[i + 2] = 'H';
            currentRelativeHumidity_Text[i + 3] = '\0';
            break;
        }
    }

    uint16_t currentRelativeHumidity_Text_width = Get_DrawedStringSize_EN(currentRelativeHumidity_Text, &CURRENT_HUMIDITY_FONT);
    Paint_DrawString_EN(CURRENT_HUMIDITY_POSITON_X, CURRENT_HUMIDITY_POSITON_Y, currentRelativeHumidity_Text, &CURRENT_HUMIDITY_FONT, WHITE, BLACK);

    // Wind Direction and speed
    char currentWindSpeed_Text[12];
    sprintf(currentWindSpeed_Text, "%.1f", weatherAPI_getCurrentWindSpeed());

    for (int i = 0; i < sizeof(currentWindSpeed_Text); i++)
    {
        if (currentWindSpeed_Text[i] == '\0')
        {
            currentWindSpeed_Text[i] = 'k';
            currentWindSpeed_Text[i + 1] = 'm';
            currentWindSpeed_Text[i + 2] = '/';
            currentWindSpeed_Text[i + 3] = 'h';
            currentWindSpeed_Text[i + 4] = '\0';
            break;
        }
    }

    uint16_t currentWindSpeed_Text_width = Get_DrawedStringSize_EN(currentWindSpeed_Text, &CURRENT_WIND_SPEED_FONT);
    Paint_DrawString_EN(CURRENT_WIND_SPEED_POSITION_X, CURRENT_WIND_SPEED_POSITION_Y, currentWindSpeed_Text, &CURRENT_WIND_SPEED_FONT, WHITE, BLACK);

    int currentWindDirection = weatherAPI_getCurrentWindDirection();
    // von 338 bis 360 und 0 bis 23
    if ((currentWindDirection > 338) || (currentWindDirection <= 23))
    {
        // North
        Paint_DrawImage(north_16x16_bits, CURRENT_WIND_SPEED_ICON_POSITION_X, CURRENT_WIND_SPEED_ICON_POSITION_Y, north_16x16_width, north_16x16_height);
    }
    else if ((currentWindDirection > 23) && (currentWindDirection <= 68))
    {
        // North-East
        Paint_DrawImage(north_east_16x16_bits, CURRENT_WIND_SPEED_ICON_POSITION_X, CURRENT_WIND_SPEED_ICON_POSITION_Y, north_east_16x16_width, north_east_16x16_height);
    }
    else if ((currentWindDirection > 68) && (currentWindDirection <= 113))
    {
        // East
        Paint_DrawImage(east_16x16_bits, CURRENT_WIND_SPEED_ICON_POSITION_X, CURRENT_WIND_SPEED_ICON_POSITION_Y, east_16x16_width, east_16x16_height);
    }
    else if ((currentWindDirection > 113) && (currentWindDirection <= 158))
    {
        // South-East
        Paint_DrawImage(south_east_16x16_bits, CURRENT_WIND_SPEED_ICON_POSITION_X, CURRENT_WIND_SPEED_ICON_POSITION_Y, south_east_16x16_width, south_east_16x16_height);
    }
    else if ((currentWindDirection > 158) && (currentWindDirection <= 203))
    {
        // South
        Paint_DrawImage(south_16x16_bits, CURRENT_WIND_SPEED_ICON_POSITION_X, CURRENT_WIND_SPEED_ICON_POSITION_Y, south_16x16_width, south_16x16_height);
    }
    else if ((currentWindDirection > 203) && (currentWindDirection <= 248))
    {
        // South-West
        Paint_DrawImage(south_west_16x16_bits, CURRENT_WIND_SPEED_ICON_POSITION_X, CURRENT_WIND_SPEED_ICON_POSITION_Y, south_west_16x16_width, south_west_16x16_height);
    }
    else if ((currentWindDirection > 248) && (currentWindDirection <= 293))
    {
        // West
        Paint_DrawImage(west_16x16_bits, CURRENT_WIND_SPEED_ICON_POSITION_X, CURRENT_WIND_SPEED_ICON_POSITION_Y, west_16x16_width, west_16x16_height);
    }
    else if ((currentWindDirection > 293) && (currentWindDirection <= 338))
    {
        // North-West
        Paint_DrawImage(north_west_16x16_bits, CURRENT_WIND_SPEED_ICON_POSITION_X, CURRENT_WIND_SPEED_ICON_POSITION_Y, north_west_16x16_width, north_west_16x16_height);
    }
}

void displayManager_generateTodaysWeather()
{
    displayManager_generate_TodaysCurrentTemperature();
    displayManager_generateTodaysSunriseAndSunsetTimes();
    displayManager_generateTodaysMinMaxTemperatures();
    displayManager_generateTodaysPrecipitation_and_CloudCover();
    displayManager_generateTodaysWindAndHumidity();
}

// .-----------------.
// | ___       _ _   |
// ||_ _|_ __ (_) |_ |
// | | || '_ \| | __||
// | | || | | | | |_ |
// ||___|_| |_|_|\__||
// '-----------------'

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

// .-----------------------------------------------------------------.
// |                 _       _       ____  _           _             |
// | _   _ _ __   __| | __ _| |_ ___|  _ \(_)___ _ __ | | __ _ _   _ |
// || | | | '_ \ / _` |/ _` | __/ _ \ | | | / __| '_ \| |/ _` | | | ||
// || |_| | |_) | (_| | (_| | ||  __/ |_| | \__ \ |_) | | (_| | |_| ||
// | \__,_| .__/ \__,_|\__,_|\__\___|____/|_|___/ .__/|_|\__,_|\__, ||
// |      |_|                                   |_|            |___/ |
// '-----------------------------------------------------------------'

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