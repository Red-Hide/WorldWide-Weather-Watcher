#include "Sensors.h"

bool SDCard_Errors(const char *path) {
    if (!file.open(path)) {
        state = erreur_SD;
        return true;
    }
    return false;
}

bool SDCard_Space(){ // use card.card() to return pointer
    uint32_t totalSpace = card.blocksPerCluster() * card.clusterCount() /1024;
    uint32_t usedSpace = card.blocksPerCluster() * (card.clusterCount() - card.fatCount()) /1024;

    if (usedSpace >= totalSpace) {
        state = SD_FULL;
        return true;
   }
   return false;
}

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
   return false;
}