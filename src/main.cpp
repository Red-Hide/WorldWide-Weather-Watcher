#include "Sensors.h"
#include <EEPROM.h>

void setup()
{
  initSensors();
  //ResetDefault();
  Configuration();
}

void loop()
{
  unsigned long TimeStart = millis();
  uint8_t interval;
  if (state == economique)
  {
    interval = EEPROM.read(config_addr) * 2;
  }
  else
  {
    interval = EEPROM.read(config_addr);
  }

  while ((millis() - TimeStart) < 1000)
  {
  }

  String mesures("");
  mesures += acquisition();
  if (state == maintenance)
  {
    Serial.println(mesures);
  }
  else
  {
    SDCardWrite(mesures);
  }
}