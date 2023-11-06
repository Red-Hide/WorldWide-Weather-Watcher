#include "Sensors.h"
#include <EEPROM.h>

bool SDCard_Errors() {
    SdFat32 card;
    if (!card.begin()) {
        card.end();
        return true;
    }   
    card.end();
    return false;
}

bool SDCard_Space(){ // use card.card() to return pointer
    SdFat32 card;
    card.begin();
    uint32_t totalSpace = card.sectorsPerCluster() * card.clusterCount() /1024;
    uint32_t usedSpace = card.sectorsPerCluster() * (card.clusterCount() - card.fatCount()) /1024;

    if (usedSpace >= totalSpace) {
        card.end();
        return true;
   }
   card.end();
   return false;
}

bool GPS_error(){
    SoftwareSerial SoftSerial(6,7);
    SoftSerial.begin(9600);
    unsigned long TimeStart = millis();
    while (millis() - TimeStart < EEPROM.read(config_addr+3)*1000)
    {
        if (SoftSerial.isListening())
        {
            SoftSerial.end();
            return false;
        }
    }
    SoftSerial.end();
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