#ifndef SD_CARD_H
#define SD_CARD_H
#include <Arduino.h>
#include <SdFat.h>

SdFat32 card;
FatFile file;

void SDCardWrite(String x);
void SDCardRead(String y);

#endif