#include "ChangeMode.h"


int state = standard;
stateList etats;

void Interruption_boutonV()
{
  static unsigned long time;
  static bool pressed = false;
  bool isPressed = digitalRead(greenInterruptBtn);
  if (!isPressed && !pressed)
  {
    time = millis();
    pressed = !pressed;
  }else if(isPressed && pressed){
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
  bool isPressed = digitalRead(redInterruptBtn);
  if (!isPressed && !pressed)
  {
    time = millis();
    pressed = !pressed;
  }else if(isPressed && pressed){
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
