// .----------------------------------------.
// | ___            _           _           |
// ||_ _|_ __   ___| |_   _  __| | ___  ___ |
// | | || '_ \ / __| | | | |/ _` |/ _ \/ __||
// | | || | | | (__| | |_| | (_| |  __/\__ \|
// ||___|_| |_|\___|_|\__,_|\__,_|\___||___/|
// '----------------------------------------'
#include <Wire.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>

// .----------------------------------.
// | ____        __ _                 |
// ||  _ \  ___ / _(_)_ __   ___  ___ |
// || | | |/ _ \ |_| | '_ \ / _ \/ __||
// || |_| |  __/  _| | | | |  __/\__ \|
// ||____/ \___|_| |_|_| |_|\___||___/|
// '----------------------------------'
#define TEMP_SENSOR_I2C_ADDRESS 0x18

// Register definitions
#define TEMP_SENSOR_T_UPPER_REG 0x02
#define TEMP_SENSOR_T_LOWER_REG 0x03
#define TEMP_SENSOR_T_CRIT_REG 0x04
#define TEMP_SENSOR_T_A_REG 0x05
#define TEMP_SENSOR_MANUFACTURER_ID_REG 0x06
#define TEMP_SENSOR_DEVICE_ID_REG 0x07
#define TEMP_SENSOR_RESOLUTION_REG 0x08

// Register objects
Adafruit_I2CDevice temperatureSensor = Adafruit_I2CDevice(TEMP_SENSOR_I2C_ADDRESS);
Adafruit_BusIO_Register id_reg(&temperatureSensor, TEMP_SENSOR_DEVICE_ID_REG, 1, LSBFIRST);
Adafruit_BusIO_Register temp_reg(&temperatureSensor, TEMP_SENSOR_T_A_REG, 2, MSBFIRST);

// .---------------------------------------------.
// | _____                 _   _                 |
// ||  ___|   _ _ __   ___| |_(_) ___  _ __  ___ |
// || |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __||
// ||  _|| |_| | | | | (__| |_| | (_) | | | \__ \|
// ||_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/|
// '---------------------------------------------'

// initialization of the temperature sensor
void tempSensor_init()
{
    if (!temperatureSensor.begin())
    {
        Serial.println("Sensor not found!");
        while (1)
            ;
    }

    uint8_t id = id_reg.read(); // liest 1 Byte

    Serial.print("Temp Sensor ID: 0x");
    Serial.println(id, HEX);

    if (id == 0x04)
    {
        {
            Serial.println("Temp Sensor correctly detected.");
        }
    }
}

// get temperature in degree Celsius
float tempSensor_getTemperature()
{
    uint16_t temp_rawBytes = temp_reg.read();
    uint8_t temp_upperByte = (temp_rawBytes >> 8) & 0x1F;
    uint8_t temp_lowerByte = temp_rawBytes & 0xFF;

    float temp = 0.0;
    if ((temp_upperByte & 0x10) == 0x10)
    {
        temp_upperByte = temp_upperByte & 0x0F;
        return (256 - ((temp_upperByte * 16.00) + (temp_lowerByte / 16.00)));
    }
    else
    {
        return (((temp_upperByte * 16.00) + (temp_lowerByte / 16.00)));
    }
}