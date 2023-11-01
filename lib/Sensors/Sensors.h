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

extern ChainableLED leds; // pin 7 et 8 sur une LED
extern BME280I2C bme;
extern RTC_DS1307 clock;
extern SoftwareSerial SoftSerial;

String getDate();

void initInterrupt();
void initSensors();
void initBME280();
void initRTC();

bool SDCard_Errors();
bool SDCard_Space();
bool GPS_error();
bool BME_error();
bool RTC_error();

#endif