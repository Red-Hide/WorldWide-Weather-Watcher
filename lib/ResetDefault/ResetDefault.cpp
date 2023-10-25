#include "ResetDefault.h"
#include <EEPROM.h>

void ResetDefault(){
    uint8_t addr = 0;
    if(EEPROM.read(addr) == 255){
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
        EEPROM.put(addr,time_config);
        addr += sizeof(time_config);
        EEPROM.put(addr,config_values);
        clock.fillByYMD(time_config.year,time_config.month,time_config.day);
        clock.fillByHMS(time_config.hours,time_config.minutes,time_config.seconds);
        clock.fillDayOfWeek(time_config.dayOfW);
    }
}