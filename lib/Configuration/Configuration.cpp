#include "Configuration.h"
#include <EEPROM.h>

void ResetDefault(){
    uint8_t addr = 0;
    switch (EEPROM.read(addr))
    {
    case 255:
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
        break;
    }
}

void Configuration(){
    if(!digitalRead(redInterruptBtn)){
        ChangeLEDStatus(configuration);
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
                        Serial.write(EEPROM.read(config_addr+4));
                    }
                }else{
                    Update(command.substring(0,index),command.substring(index+1));
                }
            }
        }
    }
    ChangeLEDStatus(standard);
}

bool checkValue(const int &val, char type)
{
    switch (type)
    {
        case 'c': //condition
            return val == 1;
        case 'l': //lumière
            return (val >= 0 && val <= 1023);
        case 't': //temperature OU hygrométrie
            return (val >= -40 && val <= 85);
        case 'p': //pression
            return (val >= 300 && val <= 1100);
    }
}

void Update(const String &command, const String &value)
{

    if(command.equalsIgnoreCase("CLOCK") && CountChar(value,':') == 2)
    {
        uint8_t hour = value.substring(0,value.indexOf(":")).toInt();
        uint8_t minutes = value.substring(value.indexOf(":")+1,value.lastIndexOf(":")).toInt();
        uint8_t seconds = value.substring(value.lastIndexOf(":")+1).toInt();
        if(hour < 0 || hour > 24 || minutes < 0 || minutes > 59 || seconds < 0 || seconds > 59){
            return;
        }else{clock.adjust(DateTime(clock.now().year(),clock.now().month(),clock.now().day(),hour,minutes,seconds));}
    }
    else if(command.equalsIgnoreCase("DATE") && CountChar(value,':') == 2)
    {
        uint8_t month = value.substring(0,value.indexOf(":")).toInt();
        uint8_t day = value.substring(value.indexOf(":")+1,value.lastIndexOf(":")).toInt();
        uint16_t year = value.substring(value.lastIndexOf(":")+1).toInt();
        if(month < 1 || month > 12 || day < 1 || day > 31 || year < 2000 || year > 2099){
            return;}
        else
        {clock.adjust(DateTime(year,month,day,clock.now().hour(),clock.now().minute(),clock.now().second()));}}
    else
    {
        const int val = value.toInt();
        if(command.equalsIgnoreCase("LOG_INTERVAL")){
        EEPROM.update(config_addr,val);
        }else if(command.equalsIgnoreCase("FILE_MAX_SIZE")){
        EEPROM.update(config_addr+1,highByte(val));
        EEPROM.update(config_addr+2,lowByte(val));
        }else if(command.equalsIgnoreCase("TIMEOUT")){
        EEPROM.update(config_addr+3,val);
        }else if(command.equalsIgnoreCase("LUMIN") && checkValue(val,'c') ){
        EEPROM.update(lum_addr,val);
        }else if(command.equalsIgnoreCase("LUMIN_LOW") && checkValue(val,'l')){
        EEPROM.update(lum_addr+1,highByte(val));
        EEPROM.update(lum_addr+2,lowByte(val));
        }else if(command.equalsIgnoreCase("LUMIN_HIGH") && checkValue(val,'l')){
        EEPROM.update(lum_addr+3,highByte(val));
        EEPROM.update(lum_addr+4,lowByte(val));
        }else if(command.equalsIgnoreCase("TEMP_AIR") && checkValue(val,'c')){
        EEPROM.update(temp_addr,val);
        }else if(command.equalsIgnoreCase("MIN_TEMP_AIR") && checkValue(val,'t')){
        EEPROM.update(temp_addr+1,val);
        }else if(command.equalsIgnoreCase("MAX_TEMP_AIR") && checkValue(val,'t')){
        EEPROM.update(temp_addr+2,val);
        }else if(command.equalsIgnoreCase("HYGR") && checkValue(val,'c')){
        EEPROM.update(hygro_addr,val);
        }else if(command.equalsIgnoreCase("HYGR_MINT") && checkValue(val,'t')){
        EEPROM.update(hygro_addr+1,val);
        }else if(command.equalsIgnoreCase("HYGR_MAXT") && checkValue(val,'t')){
        EEPROM.update(hygro_addr+1,val);
        }else if(command.equalsIgnoreCase("PRESSURE") && checkValue(val,'c')){
        EEPROM.update(pression_addr,val);
        }else if(command.equalsIgnoreCase("PRESSURE_MIN") && checkValue(val,'p')){
        EEPROM.update(pression_addr+1,highByte(val));
        EEPROM.update(pression_addr+2,lowByte(val));
        }else if(command.equalsIgnoreCase("PRESSURE_MAX") && checkValue(val,'p')){
        EEPROM.update(pression_addr+3,highByte(val));
        EEPROM.update(pression_addr+4,lowByte(val));
    }
    }
    
}

int CountChar(const String &string, char ch){
    uint8_t count = 0;
    for(uint8_t i = 0; i<string.length();i++){
        if(string[i] == ch) count++;
    }
    return count;
}

