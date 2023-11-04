#include "SDCard.h"
#include <Sensors.h>

SdFat32 card;

void SDCardWrite(const String& x)
{
  String date("");
  date += String(clock.now().year());
  date += String(clock.now().month());
  date += String(clock.now().day());
  File32 Donnees;
  int revisionNumber = 0;

  String fileName(date);
  fileName += "_0";
  Donnees = card.open(fileName, FILE_WRITE);

  if (Donnees)
  {
    Donnees.println(x);
    if (Donnees.size() >= 2048)
    {

      Donnees.close();
      String newFileName(date);
      newFileName += "_";
      newFileName +=  String(revisionNumber + 1);
      card.rename(fileName, newFileName);
    }
  }
  else
  {
    Serial.println(F("Error opening data file"));
  }
}
