#include "Sensors.h"
#include "SDCard.h"

void initInterrupt()
{
  pinMode(greenInterruptBtn,INPUT_PULLUP);
  pinMode(redInterruptBtn,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(greenInterruptBtn), Interruption_boutonV, CHANGE);
  attachInterrupt(digitalPinToInterrupt(redInterruptBtn), Interruption_boutonR, CHANGE);
}

void initSensors(){
  initLED();
  initInterrupt();
}

void initSD(){
  if (!card.begin(4)) {
    Serial.println("initialization failed!");
    state = erreur_SD;
    ChangeLEDStatus();
  }
  Serial.println("initialization done.");
}