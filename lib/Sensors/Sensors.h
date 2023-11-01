#ifndef SENSORS_H
#define SENSORS_H
#define LightSensor_Pin A0
#include <RTClib.h>
#include "ChangeMode.h"
#include "ChangeLEDStatus.h"
#include <ChainableLED.h>
#include "SDCard.h"
#include "BME280I2C.h"
#include "SoftwareSerial.h"
#include "Configuration.h"

extern BME280I2C bme;
extern RTC_DS1307 clock;
extern SoftwareSerial SoftSerial;

String getDate();

void initInterrupt();
void initSensors();
void initBME280();

bool SDCard_Errors(const char *path);
bool SDCard_Space();
bool GPS_error();
bool BME_error();

#endif