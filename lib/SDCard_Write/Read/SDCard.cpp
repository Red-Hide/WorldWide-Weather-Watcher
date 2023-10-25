#include <Libraries.h>

void SDCardWrite(String x){
  File Donnees;
    Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  Donnees = SD.open("test.txt", FILE_WRITE);

  if (Donnees){
    Serial.print("Writing to Donnees.txt");
    Donnees.println(x);

    Donnees.close();

  } else{
    Serial.println("error opening test.txt");
}

