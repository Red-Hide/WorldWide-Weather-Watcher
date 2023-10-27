#include <CheckErrors.h>
#include <acquisition.h>
Sd2Card card;
SdVolume volume;
SdFile root;
ChainableLED leds(7, 8, 1);

void SDCard_Errors() {
    if (!card.init(SPI_HALF_SPEED, 4)) {
        Serial.println("initialization failed. Things to check:");
        Serial.println("* is a card inserted?");
        Serial.println("* is your wiring correct?");
        Serial.println("* did you change the chipSelect pin to match your shield or module?");
        while (1);
    } else {
        Serial.println("Wiring is correct and a card is present.");
    }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32

    if (!volume.init(card)) {
        Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
        while (1);
    }

    uint32_t totalSpace = volume.blocksPerCluster() * volume.clusterCount() /1024;
    uint32_t usedSpace = volume.blocksPerCluster() * (volume.clusterCount() - volume.fatCount()) /1024;

    while (usedSpace >= totalSpace) {
        Serial.println("SD card is full.");
        leds.setColorRGB(7, 255, 0, 0); //rouge
        delay(1000);
        leds.setColorRGB(7, 255, 255, 255); //blanc
        delay(1000);
   }
   }

//Données d'un capteur incohérente
void CapteurDonneesErreur(){
    String LIGHTError = getLight();
    String BMEError = getBME();
    String GPSError = getGPS();
    String TimeError = getDate();


    if (LIGHTError == "error"){
        Serial.print("Une erreur dans le capteur lumiere a ete detecte");
        Serial.println("Un message pour dire de resoudre le probleme");
        while (1);
    }
    if (BMEError == "erreur"){
        Serial.print("Une erreur dans le capteur BME a ete detecte");
        Serial.println("Un message pour dire de resoudre le probleme");
        while (1);
    }
    if (GPSError == "GNA"){
        Serial.print("Une erreur dans le capteur GPS a ete detecte");
        Serial.println("Un message pour dire de resoudre le probleme");
        while (1);
    }
}