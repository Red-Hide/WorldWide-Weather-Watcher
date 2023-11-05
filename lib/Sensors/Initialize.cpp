#include "Sensors.h"

RTC_DS1307 clock;
ForcedClimate bme = ForcedClimate();

void initInterrupt()
{
  attachInterrupt(digitalPinToInterrupt(greenInterruptBtn), Interruption_boutonV, CHANGE);
  attachInterrupt(digitalPinToInterrupt(redInterruptBtn), Interruption_boutonR, CHANGE);
}

void initSensors(){
  pinMode(greenInterruptBtn,INPUT_PULLUP);
  pinMode(redInterruptBtn,INPUT_PULLUP);
  initInterrupt();
  bme.begin();
  initRTC();
  leds.init();
  Serial.begin(9600);
}

void initRTC(){
  if (!clock.begin())
  {
    ChangeLEDStatus(erreur_RTC);
  }
}