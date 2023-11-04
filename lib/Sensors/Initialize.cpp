#include "Sensors.h"

RTC_DS1307 clock;
SoftwareSerial SoftSerial(4,5);
BME280I2C bme;

void initInterrupt()
{
  pinMode(greenInterruptBtn,INPUT_PULLUP);
  pinMode(redInterruptBtn,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(greenInterruptBtn), Interruption_boutonV, CHANGE);
  attachInterrupt(digitalPinToInterrupt(redInterruptBtn), Interruption_boutonR, CHANGE);
}

void initSensors(){
  leds.init();
  initInterrupt();
  pinMode(greenInterruptBtn,INPUT);
  pinMode(redInterruptBtn,INPUT);
  pinMode(LightSensor_Pin, INPUT_PULLUP);
  initRTC();
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