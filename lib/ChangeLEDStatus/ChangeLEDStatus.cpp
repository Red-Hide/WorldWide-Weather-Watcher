#include <ChainableLED.h>
#include "ChangeLEDStatus.h"

ChainableLED leds(7, 8, 1);

void ChangeLEDStatus(int state)
  //Pour l'instant les 4 modes de base, pas encore de LED intermittante
{
  switch (state) 
  {
   case standard:
    leds.setColorRGB(7, 0, 255, 0); //vert
    break;
   case configuration:
    leds.setColorRGB(7, 255, 255, 0); //jaune
    break;
   case economique:
    leds.setColorRGB(7, 0, 0, 255); //bleu
    break;
   case maintenance:
    leds.setColorRGB(7, 255, 127, 0); //orange
    break;
   default:
    break;
  }
}
