#ifndef SENSORS_H
#define SENSORS_H
#define LightSensor_Pin A0

#include "Arduino.h"
#include "ChangeMode.h"
#include "SDCard.h"
#include "Configuration.h"
#include <forcedClimate.h>
#include <RTClib.h>
#include <SoftwareSerial.h>
#include <ChainableLED.h>

extern ChainableLED leds; // pin 7 et 8 sur une LED
extern ForcedClimate bme;
extern RTC_DS1307 clock;
extern SoftwareSerial SoftSerial;

String getDate();
String getGPS();
String getLight();
String getBME();

void initInterrupt();
void initSensors();
void initRTC();
void initSD();

bool SDCard_Errors();
bool SDCard_Space();
bool GPS_error();
bool RTC_error();

String acquisition();

#endif