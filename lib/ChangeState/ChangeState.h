#ifndef CHANGESTATE_H
#define CHANGESTATE_H

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

void ChangeState(int actualState);

#endif