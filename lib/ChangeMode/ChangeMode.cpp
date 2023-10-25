#include <Libraries.h>

int state;
stateList etats;

// TODO : Test TimerOne with multiple buttons pressed
// TODO : Make separate file and function for switching modes.

// Permet de savoir dans quel mode retourner (standard/eco) ...
// quand on sort du mode maintenance
void initInterrupt()
{
  attachInterrupt(digitalPinToInterrupt(greenInterruptBtn), Interruption_boutonV, RISING);
  attachInterrupt(digitalPinToInterrupt(redInterruptBtn), Interruption_boutonR, RISING);
  Timer1.initialize(5000000);
}

void Interruption_boutonV()
{
  // voir si cette instruction est necessaire
  // c-à-d si il faut desactiver l'interrupt pour en lancer une autre
  Timer1.detachInterrupt();
  Timer1.attachInterrupt(Interruption_timerV);
}

void Interruption_timerV()
{
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
  Timer1.detachInterrupt();
  Timer1.attachInterrupt(Interruption_timerR);
}

void Interruption_timerR()
{
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
