// .----------------------------------------.
// | ___            _           _           |
// ||_ _|_ __   ___| |_   _  __| | ___  ___ |
// | | || '_ \ / __| | | | |/ _` |/ _ \/ __||
// | | || | | | (__| | |_| | (_| |  __/\__ \|
// ||___|_| |_|\___|_|\__,_|\__,_|\___||___/|
// '----------------------------------------'

#include "RTCManager.h"

// .----------------------------------.
// | ____        __ _                 |
// ||  _ \  ___ / _(_)_ __   ___  ___ |
// || | | |/ _ \ |_| | '_ \ / _ \/ __||
// || |_| |  __/  _| | | | |  __/\__ \|
// ||____/ \___|_| |_|_| |_|\___||___/|
// '----------------------------------'
#define RTC_I2C_ADDRESS 0x68

#define RTC_SECONDS_REG 0x00
#define RTC_MINUTES_REG 0x01
#define RTC_HOURS_REG 0x02
#define RTC_WEEKDAY_REG 0x03
#define RTC_DATE_REG 0x04
#define RTC_MONTH_REG 0x05
#define RTC_YEAR_REG 0x06
#define RTC_ALARM1_SECONDS_REG 0x07
#define RTC_ALARM1_MINUTES_REG 0x08
#define RTC_ALARM1_HOURS_REG 0x09
#define RTC_ALARM1_DATE_DAY_REG 0x0A
#define RTC_ALARM2_MINUTES_REG 0x0B
#define RTC_ALARM2_HOURS_REG 0x0C
#define RTC_ALARM2_DATE_DAY_REG 0x0D
#define RTC_CONTROL_REG 0x0E
#define RTC_STATUS_REG 0x0F
#define RTC_AGING_OFFSET_REG 0x10
#define RTC_TEMPERATURE_MSB_REG 0x11
#define RTC_TEMPERATURE_LSB_REG 0x12

Adafruit_I2CDevice RealTimeClock = Adafruit_I2CDevice(RTC_I2C_ADDRESS);
Adafruit_BusIO_Register rtc_sec_Reg(&RealTimeClock, RTC_SECONDS_REG, 1, MSBFIRST);
Adafruit_BusIO_Register rtc_minutes_Reg(&RealTimeClock, RTC_MINUTES_REG, 1, MSBFIRST);
Adafruit_BusIO_Register rtc_hours_Reg(&RealTimeClock, RTC_HOURS_REG, 1, MSBFIRST);
Adafruit_BusIO_Register rtc_weekday_Reg(&RealTimeClock, RTC_WEEKDAY_REG, 1, MSBFIRST);
Adafruit_BusIO_Register rtc_date_Reg(&RealTimeClock, RTC_DATE_REG, 1, MSBFIRST);
Adafruit_BusIO_Register rtc_month_Reg(&RealTimeClock, RTC_MONTH_REG, 1, MSBFIRST);
Adafruit_BusIO_Register rtc_year_Reg(&RealTimeClock, RTC_YEAR_REG, 1, MSBFIRST);

uint8_t rtc_seconds = 0;
uint8_t rtc_secondsByte = 0;
uint8_t rtc_minutes = 0;
uint8_t rtc_minutesByte = 0;
uint8_t rtc_hours = 0;
uint8_t rtc_hoursByte = 0;
uint8_t rtc_weekday = 0;
uint8_t rtc_date = 0;
uint8_t rtc_dateByte = 0;
uint8_t rtc_month = 0;
uint8_t rtc_monthByte = 0;
uint16_t rtc_year = 0;
uint8_t rtc_yearByte = 0;

String weekDays[8] = {" ", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag", "Sonntag"};
String englischeWeekDays[8] = {" ", "\"Monday\"", "\"Tuesday\"", "\"Wednesday\"", "\"Thursday\"", "\"Friday\"", "\"Saturday\"", "\"Sunday\""};

// .---------------------------------------------.
// | _____                 _   _                 |
// ||  ___|   _ _ __   ___| |_(_) ___  _ __  ___ |
// || |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __||
// ||  _|| |_| | | | | (__| |_| | (_) | | | \__ \|
// ||_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/|
// '---------------------------------------------'

void rtc_init()
{
    timeAPI_init();
    timeAPI_updateTime();
    timeAPI_printTime();

    rtc_seconds = timeAPI_getSeconds();
    uint8_t rtc_secondsByte = ((rtc_seconds / 10) << 4) | (rtc_seconds % 10);
    rtc_sec_Reg.write(rtc_secondsByte);

    rtc_minutes = timeAPI_getMinutes();
    uint8_t rtc_minutesByte = ((rtc_minutes / 10) << 4) | (rtc_minutes % 10);
    rtc_minutes_Reg.write(rtc_minutesByte);

    rtc_hours = timeAPI_getHour();
    uint8_t rtc_hoursByte = ((rtc_hours / 10) << 4) | (rtc_hours % 10) & 0b10111111; // 24-H Format
    rtc_hours_Reg.write(rtc_hoursByte);

    rtc_date = timeAPI_getDay();
    uint8_t rtc_dateByte = ((rtc_date / 10) << 4) | (rtc_date % 10);
    rtc_date_Reg.write(rtc_dateByte);

    rtc_month = timeAPI_getMonth();
    uint8_t rtc_monthByte = ((rtc_month / 10) << 4) | (rtc_month % 10);
    rtc_month_Reg.write(rtc_monthByte);

    rtc_year = timeAPI_getYear();
    uint8_t rtc_yearByte = (((rtc_year / 10) % 10) << 4) | (rtc_year % 10);
    rtc_year_Reg.write(rtc_yearByte);

    for (uint8_t i = 1; i <= 8; i++)
    {
        if (englischeWeekDays[i] == timeAPI_getWeekday())
        {
            rtc_weekday = i;
            rtc_weekday_Reg.write(rtc_weekday);
            break;
        }
    }
}

void rtc_updateTime()
{
    rtc_seconds = (((rtc_sec_Reg.read() & 0x70) >> 4) * 10) + (rtc_sec_Reg.read() & 0x0F);
    rtc_minutes = (((rtc_minutes_Reg.read() & 0x70) >> 4) * 10) + (rtc_minutes_Reg.read() & 0x0F);
    rtc_hours = (((rtc_hours_Reg.read() & 0x30) >> 4) * 10) + (rtc_hours_Reg.read() & 0x0F);
    rtc_date = (((rtc_date_Reg.read() & 0x30) >> 4) * 10) + (rtc_date_Reg.read() & 0x0F);
    rtc_month = (((rtc_month_Reg.read() & 0x10) >> 4) * 10) + (rtc_month_Reg.read() & 0x0F);
    rtc_year = 2000 + ((((rtc_year_Reg.read() & 0xF0) >> 4) * 10) + (rtc_year_Reg.read() & 0x0F));
    rtc_weekday = rtc_weekday_Reg.read() & 0x07;
}

void rtc_printTime()
{
    Serial.print("RTC Time: ");
    Serial.print(rtc_hours);
    Serial.print(":");
    Serial.print(rtc_minutes);
    Serial.print(":");
    Serial.print(rtc_seconds);
    Serial.print(" ");
    Serial.print(rtc_date);
    Serial.print(".");
    Serial.print(rtc_month);
    Serial.print(".");
    Serial.print(rtc_year);
    Serial.println("");
}

uint8_t rtc_getSeconds()
{
    return rtc_seconds;
}

uint8_t rtc_getMinutes()
{
    return rtc_minutes;
}
uint8_t rtc_getHour()
{
    return rtc_hours;
}
uint8_t rtc_getDay()
{
    return rtc_date;
}
uint8_t rtc_getMonth()
{
    return rtc_month;
}
uint16_t rtc_getYear()
{
    return rtc_year;
}
String rtc_getWeekday()
{
    return weekDays[rtc_weekday];
}