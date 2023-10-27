#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#define config_timeout 30
#define lum_addr 1
#define temp_addr lum_addr+sizeof(lum)
#define hygro_addr temp_addr+sizeof(temp)
#define pression_addr hygro_addr+sizeof(hygro)
#define config_addr pression_addr+sizeof(pression)

#include <EEPROM.h>
#include "Configuration.h"
#include "ChangeLEDStatus.h"
#include <DS1307.h>

typedef struct{
    bool lumin = 1;
    uint16_t lumin_low = 255;
    uint16_t lumin_high = 768;
}lum;

typedef struct{
    bool temp_air = 1;
    int8_t min_temp_air = -10;
    int8_t max_temp_air = 60;
}temp;

typedef struct
{
    bool hygr = 1;
    int8_t hygr_mint = 0;
    int8_t hygr_maxt = 50;
}hygro;

typedef struct
{
    bool pressure = 1;
    uint16_t pressure_min = 850;
    uint16_t pressure_max = 1080;
}pression;

typedef struct
{
    uint16_t year = 2023;
    uint8_t month = 10;
    uint8_t day = 25;
    uint8_t hours = 12;
    uint8_t minutes = 00;
    uint8_t seconds = 00;
    uint8_t dayOfW = WED;
}time;

typedef struct 
{
    uint8_t log_interval = 10;
    uint16_t file_max_size = 4096;
    uint8_t timeout = 30;
    uint8_t version = 1;
}config;

void ResetDefault();
void Configuration();
void Update(String command, String value);

#endif