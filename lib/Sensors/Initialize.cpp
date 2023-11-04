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
    Serial.println(F("initialization failed!"));
    state = erreur_SD;
    ChangeLEDStatus();
  }
  Serial.println(F("initialization done."));
}

void initBME280(){
  while(!bme.begin())
  {
    Serial.println(F("Could not find BME280 sensor!"));
    state = erreur_BME;
    ChangeLEDStatus();
  }
}

void initRTC(){
  if (!clock.begin())
  {
    state = erreur_RTC;
    ChangeLEDStatus();
  }
}