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
erreur_CAP,
erreur_DATA,
SD_FULL,
erreur_SD
};

extern stateList etats;
extern int state;

void initInterrupt();
void Interruption_boutonV(); 
void Interruption_timerV(); 
void Interruption_boutonR();
void Interruption_timerR(); 

#endif