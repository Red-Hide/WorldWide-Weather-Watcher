#ifndef SENSORS_H
#define SENSORS_H
#define LightSensor_Pin A0
#include <DS1307.h>
#include "ChangeMode.h"
#include "ChangeLEDStatus.h"
#include <ChainableLED.h>
#include "SDCard.h"
#include "BME280I2C.h"
#include "SoftwareSerial.h"

extern BME280I2C bme;
extern DS1307 clock;
extern SoftwareSerial SoftSerial;

String getDate();
void initInterrupt();
void initSensors();
bool SDCard_Errors(const char *path);
bool SDCard_Space();
void initBME280();

#endif