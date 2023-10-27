#include "Initialize.h"
#include "SDCard.h"

void initInterrupt()
{
  pinMode(greenInterruptBtn,INPUT_PULLUP);
  pinMode(redInterruptBtn,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(greenInterruptBtn), Interruption_boutonV, FALLING);
  attachInterrupt(digitalPinToInterrupt(redInterruptBtn), Interruption_boutonR, FALLING);
  Timer1.initialize(5000000);
}

void initSensors(){
  initLED();
  initInterrupt();
}

void initSD(){
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    state = erreur_SD;
    ChangeLEDStatus();
  }
  Serial.println("initialization done.");
}