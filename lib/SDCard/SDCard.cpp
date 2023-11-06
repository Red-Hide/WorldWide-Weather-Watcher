#include "SDCard.h"
#include <Sensors.h>

void SDCardWrite(String x)
{
  SdFat card;
  if (!card.begin(4))
  {

  }

  String date = "";
  date += String(clock.now().year());
  date += String(clock.now().month());
  date += String(clock.now().day());
  File32 Donnees;
  static int revisionNumber = 0;

  String fileName = date;
  fileName += "_0.LOG";
  String newFileName = fileName;

  Donnees = card.open(fileName.c_str(), FILE_WRITE);

  if (Donnees)
  {
    Donnees.println(x);
    if (Donnees.size() >= 2048)
    {
      while (card.exists(newFileName))
      {
        revisionNumber++;
        newFileName = date + "_" + String(revisionNumber) + ".LOG";
      }
      card.rename(fileName, newFileName);
    }
  }else{
    Serial.println("ErrF");
  }
  Donnees.close();
  card.end();
}
