#include <Arduino.h>
#include "Sensors.h"
#include <EEPROM.h>

int main(){
  initSensors();
  ResetDefault();
  Configuration();
  while (true)
  {
    unsigned long TimeStart = millis();
    uint8_t interval;
    if (state == economique)
    {
      interval = EEPROM.read(config_addr) * 2;
    }else{
      interval = EEPROM.read(config_addr);
    }
    
    while (millis() - TimeStart < interval * 60UL * 1000UL){}
    
    String mesures;
    mesures += acquisition();

    if (state == maintenance){Serial.println(mesures);}else{SDCardWrite(mesures);}
  }
}