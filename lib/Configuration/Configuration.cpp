#include "Configuration.h"
#include <EEPROM.h>

void ResetDefault(){
    uint8_t addr = 0;
    if(EEPROM.read(addr) == 255){
        Serial.println(F("Reseting values to default"));
        const lum lum_config;
        const temp temp_config;
        const hygro hygro_config;
        const pression pression_config;
        const time time_config;
        const config config_values;
        EEPROM.update(addr,1);
        addr += 1;
        EEPROM.put(addr,lum_config);
        addr += sizeof(lum_config);
        EEPROM.put(addr,temp_config);
        addr += sizeof(temp_config);
        EEPROM.put(addr,hygro_config);
        addr += sizeof(hygro_config);
        EEPROM.put(addr,pression_config);
        addr += sizeof(pression_config);
        EEPROM.put(addr,config_values);
        clock.adjust(DateTime(time_config.year,time_config.month,time_config.day,time_config.hours,time_config.minutes,time_config.seconds));
    }
}

void Configuration(){
    if(!digitalRead(redInterruptBtn)){
        Serial.println(F("Entered configuration mode"));
        state = configuration;
        ChangeLEDStatus();
        unsigned long timeStart = millis();
        while ((millis() - timeStart) < config_timeout * 60UL * 1000UL)
        {
            if (Serial.available()){
                const String command = Serial.readString();
                const int index = command.indexOf("=");
                if(index == -1){
                    if(command.equalsIgnoreCase("RESET")){
                        EEPROM.update(0,255);
                        ResetDefault();
                    }else if(command.equalsIgnoreCase("VERSION")){
                        Serial.print(F("Version : "));
                        Serial.println(EEPROM.read(config_addr+4));
                    }else{
                        Serial.println(F("Error : Command not found. Please try another one."));
                    }
                }else{
                    Update(command.substring(0,index),command.substring(index+1));
                }
            }
        }
    }
    state = standard;
    ChangeLEDStatus();
}

void Update(const String &command, const String &value){
    if(command.equalsIgnoreCase("LOG_INTERVAL")){
        EEPROM.update(config_addr,value.toInt());
    }else if(command.equalsIgnoreCase("FILE_MAX_SIZE")){
        EEPROM.update(config_addr+1,highByte(value.toInt()));
        EEPROM.update(config_addr+2,lowByte(value.toInt()));
    }else if(command.equalsIgnoreCase("TIMEOUT")){
        EEPROM.update(config_addr+3,value.toInt());
    }else if(command.equalsIgnoreCase("LUMIN") && value.toInt() <= 1 && value.toInt() >= 0){
        EEPROM.update(lum_addr,value.toInt());
    }else if(command.equalsIgnoreCase("LUMIN_LOW") && value.toInt() >= 0 && value.toInt() <= 1023){
        EEPROM.update(lum_addr+1,highByte(value.toInt()));
        EEPROM.update(lum_addr+2,lowByte(value.toInt()));
    }else if(command.equalsIgnoreCase("LUMIN_HIGH") && value.toInt() >= 0 && value.toInt() <= 1023){
        EEPROM.update(lum_addr+3,highByte(value.toInt()));
        EEPROM.update(lum_addr+4,lowByte(value.toInt()));
    }else if(command.equalsIgnoreCase("TEMP_AIR") && value.toInt() <= 1 && value.toInt() >= 0){
        EEPROM.update(temp_addr,value.toInt());
    }else if(command.equalsIgnoreCase("MIN_TEMP_AIR") && value.toInt() >= -40 && value.toInt() <= 85){
        EEPROM.update(temp_addr+1,value.toInt());
    }else if(command.equalsIgnoreCase("MAX_TEMP_AIR") && value.toInt() >= -40 && value.toInt() <= 85){
        EEPROM.update(temp_addr+2,value.toInt());
    }else if(command.equalsIgnoreCase("HYGR") && value.toInt() <= 1 && value.toInt() >= 0){
        EEPROM.update(hygro_addr,value.toInt());
    }else if(command.equalsIgnoreCase("HYGR_MINT") && value.toInt() >= -40 && value.toInt() <= 85){
        EEPROM.update(hygro_addr+1,value.toInt());
    }else if(command.equalsIgnoreCase("HYGR_MAXT") && value.toInt() >= -40 && value.toInt() <= 85){
        EEPROM.update(hygro_addr+1,value.toInt());
    }else if(command.equalsIgnoreCase("PRESSURE") && value.toInt() <= 1 && value.toInt() >= 0){
        EEPROM.update(pression_addr,value.toInt());
    }else if(command.equalsIgnoreCase("PRESSURE_MIN") && value.toInt() >= 300 && value.toInt() <= 1100){
        EEPROM.update(pression_addr+1,highByte(value.toInt()));
        EEPROM.update(pression_addr+2,lowByte(value.toInt()));
    }else if(command.equalsIgnoreCase("PRESSURE_MAX") && value.toInt() >= 300 && value.toInt() <= 1100){
        EEPROM.update(pression_addr+3,highByte(value.toInt()));
        EEPROM.update(pression_addr+4,lowByte(value.toInt()));
    }else if(command.equalsIgnoreCase("CLOCK") && CountChar(value,':') == 2){
        uint8_t hour = value.substring(0,value.indexOf(":")).toInt();
        uint8_t minutes = value.substring(value.indexOf(":")+1,value.lastIndexOf(":")).toInt();
        uint8_t seconds = value.substring(value.lastIndexOf(":")+1).toInt();
        if(hour < 0 || hour > 24 || minutes < 0 || minutes > 59 || seconds < 0 || seconds > 59){
            Serial.println(F("Error : Please enter a valid clock time"));
            return;
        }else{clock.adjust(DateTime(clock.now().year(),clock.now().month(),clock.now().day(),hour,minutes,seconds));}
    }else if(command.equalsIgnoreCase("DATE") && CountChar(value,':') == 2){
        uint8_t month = value.substring(0,value.indexOf(":")).toInt();
        uint8_t day = value.substring(value.indexOf(":")+1,value.lastIndexOf(":")).toInt();
        uint16_t year = value.substring(value.lastIndexOf(":")+1).toInt();
        if(month < 1 || month > 12 || day < 1 || day > 31 || year < 2000 || year > 2099){
            Serial.println(F("Error : Please enter a valid date"));
            return;
        }else{clock.adjust(DateTime(year,month,day,clock.now().hour(),clock.now().minute(),clock.now().second()));}
    }else{
        Serial.println(F("Error : Please enter a valid value"));
        return;
    }
    Serial.println(F("Success : Configuration successfully updated"));
}

int CountChar(const String &string, char ch){
    uint8_t count = 0;
    for(uint8_t i = 0; i<string.length();i++){
        if(string[i] == ch) count++;
    }
    return count;
}