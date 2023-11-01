#include "SDCard.h"
#include <Sensors.h>
#include <Arduino.h>
#include <SdFat.h>

SdFat32 card;
FatFile file;
SdFat SD;
void SDCardWrite(String x)
{
  String date = String(clock.now().year()) + String(clock.now().month()) + String(clock.now().day());
  File Donnees;
  int revisionNumber = 0;

  String fileName = date + "_0";
  Donnees = SD.open(fileName, FILE_WRITE);

  if (Donnees)
  {
    Serial.print("Writing Data");
    Donnees.println(x);
    if (Donnees.size() >= 2048)
    {

      Donnees.close();
      String newFileName = date + "_" + String(revisionNumber + 1);
      SD.rename(fileName, newFileName);
    }
  }
  else
  {
    Serial.println("Error opening data file");
  }
}

void SDCardRead(String y)
{
  File Donnees;
  // re-open the file for reading:
  Donnees = SD.open("test.txt");
  if (Donnees)
  {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (Donnees.available())
    {
      Serial.write(Donnees.read());
    }
    // close the file:
    Donnees.close();
  }
  else
  {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
