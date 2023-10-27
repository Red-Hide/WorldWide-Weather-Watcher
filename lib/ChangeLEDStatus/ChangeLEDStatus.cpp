#include "ChangeLEDStatus.h"

ChainableLED leds(7,8,1); //pin 7 et 8 sur une LED

void ChangeLEDStatus()
  // TODO: Pour l'instant les 4 modes de base, pas encore de LED intermittante
  // TODO: Create function to init
{
  switch (state) 
  {
   case standard:
    leds.setColorRGB(0, 0, 20, 0); //vert
    break;
   case configuration:
    leds.setColorRGB(0, 20, 20, 0); //jaune
    break;
   case economique:
    leds.setColorRGB(0, 0, 0, 20); //bleu
    break;
   case maintenance:
    leds.setColorRGB(0, 20, 10, 0); //orange
    break;
   default:
    break;
  }
}

void initLED(){
  leds.init();
}