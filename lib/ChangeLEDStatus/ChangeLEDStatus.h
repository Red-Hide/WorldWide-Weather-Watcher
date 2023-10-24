#ifndef CHANGELEDSTATUS_H
#define CHANGELEDSTATUS_H

enum etat{
standard,
configuration,
economique,
maintenance
};

void ChangeLEDStatus(etat);

#endif