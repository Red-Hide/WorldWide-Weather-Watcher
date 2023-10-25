#ifndef RESETDEFAULT_H
#define RESETDEFAULT_H
#include <DS1307.h>

typedef struct{
    bool lumin = 1;
    uint16_t lumin_low = 255;
    uint16_t lumin_high = 768;
}lum;

typedef struct{
    bool temp_air = 1;
    int min_temp_air = -10;
    int max_temp_air = 60;
}temp;

typedef struct
{
    bool hygr = 1;
    int hygr_mint = 0;
    int hygr_maxt = 50;
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
    uint8_t version = 1;
    uint8_t timeout = 30;
}config;

extern DS1307 clock;

void ResetDefault();

#endif