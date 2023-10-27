#include "ChangeMode.h"


int state = standard;
stateList etats;

// Permet de savoir dans quel mode retourner (standard/eco) ...
// quand on sort du mode maintenance


void Interruption_boutonV()
{
  // voir si cette instruction est necessaire
  // c-à-d si il faut desactiver l'interrupt pour en lancer une autre
  Serial.println("Interrupt V");
  Timer1.detachInterrupt();
  Timer1.attachInterrupt(Interruption_timerV);
}

void Interruption_timerV()
{
  Timer1.detachInterrupt();
  Serial.println("Interrupt Timer V");
  if (digitalRead(greenInterruptBtn))
  {
    // change l'etat à l'aide d'un pointeur
    //(car on ne peut modifier une var globale dans un fct)
    switch (state)
    {
    case standard:
      state = economique;
      break;
    case economique:
      state = standard;
      break;
    }
  }
}

void Interruption_boutonR()
{
  // voir si cette instruction est necessaire
  // c-à-d si il faut desactiver l'interrupt pour en lancer une autre
  Serial.println("Interrupt R");
  Timer1.detachInterrupt();
  Timer1.attachInterrupt(Interruption_timerR);
}

void Interruption_timerR()
{
  Timer1.detachInterrupt();
  Serial.println("Interrupt Timer R");
  static bool StandardLastMode;
  if (digitalRead(redInterruptBtn))
  {
    switch (state)
    {
    case standard:
      StandardLastMode = true;
      state = maintenance;
      break;
    case economique:
      StandardLastMode = false;
      state = maintenance;
      break;
    case maintenance:
      if (StandardLastMode)
      {
        state = standard;
        break;
      }
      else
      {
        state = economique;
        break;
      }
    }
    ChangeLEDStatus();
  }
}
