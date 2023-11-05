#include "SDCard.h"
#include <Sensors.h>

void SDCardWrite(const String &x)
{
  SdFat32 card;
  card.begin(4);
  String date("");
  date += String(clock.now().year());
  date += String(clock.now().month());
  date += String(clock.now().day());
  File32 Donnees;
  static int revisionNumber = 0;

  String fileName(date);
  fileName += "_0";
  Donnees.open(fileName.c_str());

  Donnees.println(x);
  if (Donnees.size() >= 2048)
  {

    String newFileName(date);
    newFileName += "_";
    revisionNumber++;
    newFileName += String(revisionNumber);
    card.rename(fileName, newFileName);
  }
  Donnees.close();
  card.end();
}
