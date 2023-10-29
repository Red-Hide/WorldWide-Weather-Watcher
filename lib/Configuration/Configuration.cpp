#include "Configuration.h"

void ResetDefault(){
    uint8_t addr = 0;
    if(EEPROM.read(addr) == 255){
        Serial.println("Reseting values to default");
        lum lum_config;
        temp temp_config;
        hygro hygro_config;
        pression pression_config;
        time time_config;
        config config_values;
        EEPROM.write(addr,1);
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
        clock.fillByYMD(time_config.year,time_config.month,time_config.day);
        clock.fillByHMS(time_config.hours,time_config.minutes,time_config.seconds);
        clock.fillDayOfWeek(time_config.dayOfW);
    }
}

void Configuration(){
    if(!digitalRead(redInterruptBtn)){
        Serial.println("Entered configuration mode");
        state = configuration;
        ChangeLEDStatus();
        unsigned long timeStart = millis();
        while ((millis() - timeStart) < config_timeout * 60UL * 1000UL)
        {
            String command = "";
            if (Serial.available()){
                command = Serial.readString();
                command.trim();
                Serial.println(command.equalsIgnoreCase("VERSION"));
                int index = command.indexOf("=");
                if(index == -1){
                    if(command.equalsIgnoreCase("RESET")){
                        EEPROM.update(0,255);
                        ResetDefault();
                    }else if(command.equalsIgnoreCase("VERSION")){
                        config configuration;
                        EEPROM.get(config_addr,configuration);
                        Serial.println(configuration.version);
                    }else{
                        Serial.println("Error : Command not found. Please try another one.");
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

void Update(String command, String value){
    if(command.equalsIgnoreCase("LOG_INTERVAL")){
        EEPROM.write(config_addr,value.toInt());
    }else if(command.equalsIgnoreCase("FILE_MAX_SIZE")){
        EEPROM.write(config_addr+1,highByte(value.toInt()));
        EEPROM.write(config_addr+2,lowByte(value.toInt()));
    }else if(command.equalsIgnoreCase("TIMEOUT")){
        EEPROM.write(config_addr+3,value.toInt());
    }else if(command.equalsIgnoreCase("LUMIN") && value.toInt() <= 1 && value.toInt() >= 0){
        EEPROM.write(lum_addr,value.toInt());
    }else if(command.equalsIgnoreCase("LUMIN_LOW") && value.toInt() >= 0 && value.toInt() <= 1023){
        EEPROM.write(lum_addr+1,highByte(value.toInt()));
        EEPROM.write(lum_addr+2,lowByte(value.toInt()));
    }else if(command.equalsIgnoreCase("LUMIN_HIGH") && value.toInt() >= 0 && value.toInt() <= 1023){
        EEPROM.write(lum_addr+3,highByte(value.toInt()));
        EEPROM.write(lum_addr+4,lowByte(value.toInt()));
    }else if(command.equalsIgnoreCase("TEMP_AIR") && value.toInt() <= 1 && value.toInt() >= 0){
        EEPROM.write(temp_addr,value.toInt());
    }else if(command.equalsIgnoreCase("MIN_TEMP_AIR") && value.toInt() >= -40 && value.toInt() <= 85){
        EEPROM.write(temp_addr+1,value.toInt());
    }else if(command.equalsIgnoreCase("MAX_TEMP_AIR") && value.toInt() >= -40 && value.toInt() <= 85){
        EEPROM.write(temp_addr+2,value.toInt());
    }else if(command.equalsIgnoreCase("HYGR") && value.toInt() <= 1 && value.toInt() >= 0){
        EEPROM.write(hygro_addr,value.toInt());
    }else if(command.equalsIgnoreCase("HYGR_MINT") && value.toInt() >= -40 && value.toInt() <= 85){
        EEPROM.write(hygro_addr+1,value.toInt());
    }else if(command.equalsIgnoreCase("HYGR_MAXT") && value.toInt() >= -40 && value.toInt() <= 85){
        EEPROM.write(hygro_addr+1,value.toInt());
    }else if(command.equalsIgnoreCase("PRESSURE") && value.toInt() <= 1 && value.toInt() >= 0){
        EEPROM.write(pression_addr,value.toInt());
    }else if(command.equalsIgnoreCase("PRESSURE_MIN") && value.toInt() >= 300 && value.toInt() <= 1100){
        EEPROM.write(pression_addr+1,highByte(value.toInt()));
        EEPROM.write(pression_addr+2,lowByte(value.toInt()));
    }else if(command.equalsIgnoreCase("PRESSURE_MAX") && value.toInt() >= 300 && value.toInt() <= 1100){
        EEPROM.write(pression_addr+3,highByte(value.toInt()));
        EEPROM.write(pression_addr+4,lowByte(value.toInt()));
    }else if(command.equalsIgnoreCase("CLOCK") && CountChar(value,':') == 2){
        uint8_t hour = value.substring(0,value.indexOf(":")).toInt();
        uint8_t minutes = value.substring(value.indexOf(":")+1,value.lastIndexOf(":")).toInt();
        uint8_t seconds = value.substring(value.lastIndexOf(":")+1).toInt();
        if(hour < 0 || hour > 24 || minutes < 0 || minutes > 59 || seconds < 0 || seconds > 59){
            Serial.println("Error : Please enter a valid clock time");
            return;
        }else{clock.fillByHMS(hour,minutes,seconds);}
    }else if(command.equalsIgnoreCase("DATE") && CountChar(value,':') == 2){
        uint8_t month = value.substring(0,value.indexOf(":")).toInt();
        uint8_t day = value.substring(value.indexOf(":")+1,value.lastIndexOf(":")).toInt();
        uint16_t year = value.substring(value.lastIndexOf(":")+1).toInt();
        if(month < 1 || month > 12 || day < 1 || day > 31 || year < 2000 || year > 2099){
            Serial.println("Error : Please enter a valid date");
            return;
        }else{clock.fillByYMD(year,month,day);}
    }else if(command.equalsIgnoreCase("DAY")){
        if(value.equalsIgnoreCase("MON")){
            clock.fillDayOfWeek(MON);
        }else if(value.equalsIgnoreCase("TUE")){
            clock.fillDayOfWeek(TUE);
        }else if(value.equalsIgnoreCase("WED")){
            clock.fillDayOfWeek(WED);
        }else if(value.equalsIgnoreCase("THU")){
            clock.fillDayOfWeek(THU);
        }else if(value.equalsIgnoreCase("FRI")){
            clock.fillDayOfWeek(FRI);
        }else if(value.equalsIgnoreCase("SAT")){
            clock.fillDayOfWeek(SAT);
        }else if(value.equalsIgnoreCase("SUN")){
            clock.fillDayOfWeek(SUN);
        }else{
            Serial.println("Error : Please enter a valid day");
            return;
        }
    }else{
        Serial.println("Error : Please enter a valid value");
        return;
    }
    Serial.println("Success : Configuration successfully updated");
}

int CountChar(String string, char ch){
    uint8_t count = 0;
    for(uint8_t i = 0; i<string.length();i++){
        if(string[i] == ch) count++;
    }
    return count;
}