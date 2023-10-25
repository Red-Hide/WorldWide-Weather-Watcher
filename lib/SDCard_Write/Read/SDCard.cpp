#include <Libraries.h>

void SDCardWrite(String x) {
  File Donnees;
  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  Donnees = SD.open("test.txt", FILE_WRITE);

  if (Donnees) {
    Serial.print("Writing to Donnees.txt");
    Donnees.println(x);
    Donnees.close();
  } else {
    Serial.println("error opening test.txt");
  }
}

void SdCardRead(String y) {
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

