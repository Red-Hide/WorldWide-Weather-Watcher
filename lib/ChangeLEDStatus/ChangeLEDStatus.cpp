#include "ChangeLEDStatus.h"

ChainableLED leds(7, 8, 1);

void blink(char color,int duree)
{
  leds.setColorRGB(7, 255, 0, 0); //rouge
  _delay_ms(1000);
  switch (color)
  {
    case 'w':
      leds.setColorRGB(7, 255, 255, 255); //blanc 
      break;
    case 'b':
      leds.setColorRGB(7, 0, 0, 255); //bleu
      break;
    case 'g':
      leds.setColorRGB(7, 0, 255, 0); //vert
      break;
    case 'y':
      leds.setColorRGB(7, 255, 255, 0); //jaune
      break;
  }
  delay(duree);
}

void ChangeLEDStatus(int status)
{
  state = status;
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
      blink('b',1000);
    }
  case erreur_GPS:
    while (GPS_error())
    {
      blink('y',1000);
    }
  case erreur_DATA:
    for (;;)
    {
      blink('g',2000);
    }
  case SD_FULL:
    while (SDCard_Space())
    {
      blink('w',1000);
    }
  case erreur_SD:
    while (SDCard_Errors())
    {
      blink('w',2000);
    }
  }
}


