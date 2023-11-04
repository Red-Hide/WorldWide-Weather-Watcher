#include "Sensors.h"

RTC_DS1307 clock;
SoftwareSerial SoftSerial(4,5);
ForcedClimate bme = ForcedClimate();

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
  initSD();
  Serial.begin(9600);
  SoftSerial.begin(9600);
}

void initSD(){
  if (!card.begin(4)) {
    ChangeLEDStatus(erreur_SD);
  }
}

void initRTC(){
  if (!clock.begin())
  {
    ChangeLEDStatus(erreur_RTC);
  }
}