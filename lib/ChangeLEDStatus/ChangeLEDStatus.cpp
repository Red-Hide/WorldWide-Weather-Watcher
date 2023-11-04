#include "ChangeLEDStatus.h"
#include "Sensors.h"

ChainableLED leds(7, 8, 1);

void ChangeLEDStatus()
{
  switch (state)
  {
  case standard:
    leds.setColorRGB(0, 0, 20, 0); // vert
    break;
  case configuration:
    leds.setColorRGB(0, 20, 20, 0); // jaune
    break;
  case economique:
    leds.setColorRGB(0, 0, 0, 20); // bleu
    break;
  case maintenance:
    leds.setColorRGB(0, 20, 10, 0); // orange
    break;
  case erreur_RTC:
    while(RTC_error()){
      leds.setColorRGB(7, 255, 0, 0); //rouge
      delay(1000);
      leds.setColorRGB(7, 0, 0, 255); //bleu
      delay(1000);
    }
  case erreur_GPS:
    while (GPS_error())
    {
      leds.setColorRGB(7, 255, 0, 0); //rouge
      delay(1000);
      leds.setColorRGB(7, 255, 255, 0); //jaune
      delay(1000);
    }
  case erreur_BME:
    while (BME_error())
    {
      leds.setColorRGB(7, 255, 0, 0); //rouge
      delay(1000);
      leds.setColorRGB(7, 0, 255, 0); //vert
      delay(1000);
    }
  case erreur_DATA:
    while (true)
    {
      leds.setColorRGB(7, 255, 0, 0); //rouge
      delay(1000);
      leds.setColorRGB(7, 0, 255, 0); //vert
      delay(1000);
    }
  case SD_FULL:
    while (SDCard_Space())
    {
      leds.setColorRGB(7, 255, 0, 0); //rouge
      delay(1000);
      leds.setColorRGB(7, 255, 255, 255); //blanc
      delay(1000);
    }
  case erreur_SD:
    while (SDCard_Errors())
    {
      leds.setColorRGB(7, 255, 0, 0); //rouge
      delay(1000);
      leds.setColorRGB(7, 255, 255, 255); //blanc
      delay(2000);
    }
  }
}
