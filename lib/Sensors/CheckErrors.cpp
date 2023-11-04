#include "Sensors.h"
#include <EEPROM.h>

bool SDCard_Errors() {
    if (!card.begin()) {
        return true;
    }   
    return false;
}

bool SDCard_Space(){ // use card.card() to return pointer
    uint32_t totalSpace = card.sectorsPerCluster() * card.clusterCount() /1024;
    uint32_t usedSpace = card.sectorsPerCluster() * (card.clusterCount() - card.fatCount()) /1024;

    if (usedSpace >= totalSpace) {
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