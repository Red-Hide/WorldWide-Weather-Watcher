#include "ChangeState.h"
#include "ChangeLEDStatus.h"

stateList etats;
int state;

void ChangeState(int newState){
    switch (newState)
    {
    case standard:
        state = standard;
        break;
    case economique:
        state = economique;
        break;
    case maintenance:
        state = maintenance;
        break;
    case configuration:
        state = configuration;
        break;
    case erreur_CAP:
        state = erreur_CAP;
        break;
    case erreur_DATA:
        state = erreur_DATA;
        break;
    case erreur_GPS:
        state = erreur_CAP;
        break;
    case erreur_RTC:
        state = erreur_RTC;
        break;
    case erreur_SD:
        state = erreur_SD;
        break;
    case SD_FULL:
        state = SD_FULL;
        break;
    default:
        state = standard;
        break;
    }
    ChangeLEDStatus();
}