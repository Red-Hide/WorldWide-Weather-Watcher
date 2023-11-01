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

bool GPS_error(){
    unsigned long TimeStart = millis();
    while (millis() - TimeStart < EEPROM.read(config_addr+3)*1000)
    {
        if (SoftSerial.isListening())
        {
            return false;
        }
    }
    return true;
}

bool BME_error(){
    unsigned long TimeStart = millis();
    while (millis() - TimeStart < EEPROM.read(config_addr+3)*1000)
    {
        if (bme.begin())
        {
            return false;
        }
    }
    return true;
}

bool RTC_error(){
    unsigned long TimeStart = millis();
    while (millis() - TimeStart < EEPROM.read(config_addr+3)*1000)
    {
        if (clock.isrunning())
        {
            return false;
        }
    }
    return true;
}