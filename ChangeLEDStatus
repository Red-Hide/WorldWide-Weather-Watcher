#include <ChainableLED.h>

enum etat {
standard,
configuration,
economique,
maintenance
};

void setup()
{
  ChainableLED leds(7, 8, 1); //pin 7 et 8 sur une LED
}

void ChangeLEDStatus(enum etat)
  //Pour l'instant les 4 modes de base, pas encore de LED intermittante
{
  switch (etat) 
   //Verifier si bon pin
  {
   case standard:
   leds.setColorRGB(7, 0, 255, 0); //vert
   break;
   case configuration:
   leds.setColorRGB(7, 255, 255, 0); //jaune
   break;
   case eco:
   leds.setColorRGB(7, 0, 0, 255); //bleu
   break;
   case maintenance:
   leds.setColorRGB(7, 255, 127, 0); //orange
   break;
  }
}
