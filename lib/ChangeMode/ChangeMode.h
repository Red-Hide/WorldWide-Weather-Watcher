#ifndef CHANGEMODE_H
#define CHANGEMODE_H
#define greenInterruptBtn 2
#define redInterruptBtn 3
#include <TimerOne.h>
#include "ChangeLEDStatus.h"

enum stateList{
standard,
configuration,
economique,
maintenance,
erreur_RTC,
erreur_GPS,
erreur_BME,
erreur_DATA,
SD_FULL,
erreur_SD
};

extern stateList etats;
extern int state;

void Interruption_boutonV(); 
void Interruption_boutonR();

#endif