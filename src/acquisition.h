#ifndef ACQUISITION_H
#define ACQUISITION_H

#include <SoftwareSerial.h>
#include <SD.h>
#include <SDCard.h>
#include <BME280.h>
#include <BME280I2C.h>
#include <DS1307.h>

String getLight();
String getBME();
String getGPS();
String getDate();
#endif