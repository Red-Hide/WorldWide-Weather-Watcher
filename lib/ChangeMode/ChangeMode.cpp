#include "ChangeMode.h"


int state = standard;
stateList etats;

// Permet de savoir dans quel mode retourner (standard/eco) ...
// quand on sort du mode maintenance

void Interruption_boutonV()
{
  static unsigned long time;
  static bool pressed = false;
  if (!digitalRead(greenInterruptBtn) && !pressed)
  {
    // change l'etat à l'aide d'un pointeur
    //(car on ne peut modifier une var globale dans un fct)
    Serial.println("Interrupt_V");
    time = millis();
    pressed = !pressed;
  }else if(digitalRead(greenInterruptBtn) && pressed){
    pressed = !pressed;
    if(millis() - time >= 5000){
    switch (state)
    {
    case standard:
      state = economique;
      break;
    case economique:
      state = standard;
      break;
    }
    ChangeLEDStatus();
    }
  }
}

void Interruption_boutonR()
{
  static unsigned long time;
  static bool pressed = false;
  static int StandardLastMode;
  if (!digitalRead(redInterruptBtn) && !pressed)
  {
    Serial.println("Interrupt R");
    time = millis();
    pressed = !pressed;
  }else if(digitalRead(redInterruptBtn) && pressed){
    pressed = !pressed;
    if (millis() - time >= 5000)
    {
      switch (state)
    {
    case standard:
      StandardLastMode = standard;
      state = maintenance;
      break;
    case economique:
      StandardLastMode = economique;
      state = maintenance;
      break;
    case maintenance:
      if (StandardLastMode == standard)
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
}
