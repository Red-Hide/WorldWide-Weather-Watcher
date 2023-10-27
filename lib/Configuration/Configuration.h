#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#define config_timeout 30
#include <EEPROM.h>
#include "Configuration.h"
#include "ChangeLEDStatus.h"
#include "ResetDefault.h"

void Configuration();
void Update(String command, String value);

#endif