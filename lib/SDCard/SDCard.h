#ifndef SD_CARD_H
#define SD_CARD_H
#include <SdFat.h>

extern SdFat32 card;

void SDCardWrite(const String& x);

#endif