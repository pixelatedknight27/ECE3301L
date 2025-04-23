#include <stdio.h>

#include <p18f4620.h>
#include "I2C_Support.h"
#include "I2C.h"

#define ACCESS_CFG      0xAC
#define START_CONV      0xEE
#define READ_TEMP       0xAA
#define CONT_CONV       0x02
#define ACK             1
#define NAK             0

#define DS1621_ADDR     0x48
#define DS3231_ADDR     0x68



extern unsigned char second, minute, hour, dow, day, month, year;
extern unsigned char setup_second, setup_minute, setup_hour, setup_dow, setup_day, setup_month, setup_year;
extern unsigned char alarm_second, alarm_minute, alarm_hour, alarm_date;
extern unsigned char setup_alarm_second, setup_alarm_minute, setup_alarm_hour;

extern char I2C_Write_Cmd_Read_One_Byte(char Device, char Cmd);

int DS1621_Read_Temp()
{
    return (I2C_Write_Cmd_Read_One_Byte (DS1621_ADDR, READ_TEMP));
}

void DS1621_Init()
{
    I2C_Write_Cmd_Write_Data (DS1621_ADDR, ACCESS_CFG, CONT_CONV);
    I2C_Write_Cmd_Only(DS1621_ADDR, START_CONV);
}

void DS3231_Read_Time()
{
    second  = I2C_Write_Address_Read_One_Byte (DS3231_ADDR, 0x00, ACK);
    minute  = I2C_Read (ACK);
    hour    = I2C_Read (ACK);
    dow     = I2C_Read (ACK);
    day     = I2C_Read (ACK);
    month   = I2C_Read (ACK);
    year    = I2C_Read (NAK);
}

void DS3231_Setup_Time()
{
    second = setup_second;
    minute = setup_minute;
    hour = setup_hour;
    dow = setup_dow;
    day = setup_day;
    month = setup_month;
    year = setup_year;
    I2C_Write_Address_Write_One_Byte(DS3231_ADDR, 0x00, second);
    I2C_Write_Address_Write_One_Byte(DS3231_ADDR, 0x01, minute);
    I2C_Write_Address_Write_One_Byte(DS3231_ADDR, 0x02, hour);
    I2C_Write_Address_Write_One_Byte(DS3231_ADDR, 0x03, dow);
    I2C_Write_Address_Write_One_Byte(DS3231_ADDR, 0x04, day);
    I2C_Write_Address_Write_One_Byte(DS3231_ADDR, 0x05, month);
    I2C_Write_Address_Write_One_Byte(DS3231_ADDR, 0x06, year);

}

