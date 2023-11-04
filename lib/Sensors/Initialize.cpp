#include "Sensors.h"

RTC_DS1307 clock;
SoftwareSerial SoftSerial(4,5);
BME280I2C bme;

void initInterrupt()
{
  attachInterrupt(digitalPinToInterrupt(greenInterruptBtn), Interruption_boutonV, CHANGE);
  attachInterrupt(digitalPinToInterrupt(redInterruptBtn), Interruption_boutonR, CHANGE);
}

void initSensors(){
  leds.init();
  initInterrupt();
  DDRD = DDRD | B11110000;
  initRTC();
  initBME280();
  initSD();
  Serial.begin(9600);
  SoftSerial.begin(9600);
}

void initSD(){
  if (!card.begin(4)) {
    ChangeLEDStatus(erreur_SD);
  }
}

void initBME280(){
  while(!bme.begin())
  {
    ChangeLEDStatus(erreur_BME);
  }
}

void initRTC(){
  if (!clock.begin())
  {
    ChangeLEDStatus(erreur_RTC);
  }
}