#include "Sensors.h"

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

void initBME280(){
  while(!bme.begin())
  {
    Serial.println("Could not find BME280 sensor!");
    state = erreur_BME;
    ChangeLEDStatus();
  }

  switch(bme.chipModel())
  {
     case BME280::ChipModel_BME280:
       Serial.println("Found BME280 sensor! Success.");
       break;
     case BME280::ChipModel_BMP280:
       Serial.println("Found BMP280 sensor! No Humidity available.");
       break;
     default:
       state = erreur_BME;
       ChangeLEDStatus();
  }
}