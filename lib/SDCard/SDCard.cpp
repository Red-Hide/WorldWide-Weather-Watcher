#include "SDCard.h"

void SDCardWrite(String x) {
  File Donnees;

  Donnees = SD.open("test.txt", FILE_WRITE);

  if (Donnees) {
    Serial.print("Writing to Donnees.txt");
    Donnees.println(x);
    Donnees.close();
  } else {
    Serial.println("error opening test.txt");
  }
}

void SDCardRead(String y) {
  File Donnees;
   // re-open the file for reading:
  Donnees = SD.open("test.txt");
  if (Donnees) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (Donnees.available()) {
      Serial.write(Donnees.read());
    }
    // close the file:
    Donnees.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

