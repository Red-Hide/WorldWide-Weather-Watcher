#ifndef SENSORS_H
#define SENSORS_H
#include <DS1307.h>
#include "ChangeMode.h"
#include "ChangeLEDStatus.h"
#include <ChainableLED.h>
#include "SDCard.h"
#include "BME280I2C.h"

BME280I2C bme;
extern DS1307 clock;

String getDate();
void initInterrupt();
void initSensors();

bool SDCard_Errors();
bool SDCard_Space();

#endif