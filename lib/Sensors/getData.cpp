#include "Sensors.h"
#include <EEPROM.h>

String getDate()
{
  static bool timeout = false;
  String date("D:");
  bool error_rtc = RTC_error();
  if (!error_rtc)
  {
    date += String(clock.now().year());
    date += "/";
    date += String(clock.now().month());
    date += "/";
    date += String(clock.now().day());
    date += " ";
    date += String(clock.now().hour());
    date += ":";
    date += String(clock.now().minute());
    date += ":";
    date += String(clock.now().second());
  }
  else if (error_rtc && timeout)
  {
    int lastState = state;
    ChangeLEDStatus(erreur_RTC);
    timeout = false;
    ChangeLEDStatus(lastState);
  }
  else
  {
    date += "NA";
    return String(date);
  }
  return String(date);
}

String getGPS()
{
  SoftwareSerial SoftSerial(6,7);
  SoftSerial.begin(9600);
  String gps("G:");
  static bool timeout = false;
  bool error_GPS = GPS_error();
  if (!error_GPS)
  {
    if (SoftSerial.available()) 
    {
      int cond = 2;
      char tmp;        
      while (cond > 0) 
      {
        tmp = char(SoftSerial.read()); // Lit un caractère ASCII de SoftSerial et le convertit
        if (tmp == ',')                // Quand on voit une virgule
        {
          cond -= 1;
        }
      }
      // A partir de maintenant, coordonnées GPS
      cond = 1;         // Reset de la condition
      while (cond == 1) // Tant que l'on atteint pas la fin des coordonnées (le E de est ou W de Ouest)
      {
        tmp = char(SoftSerial.read()); // Lit un caractère ASCII de SoftSerial et le convertit
        gps += tmp;                    // Ajout du caractère aux coordonnées
        if (tmp == 'E' or tmp == 'W')  // Quand on voit un E ou un W
        {
          cond = 0;                      // Fin de la boucle
          while (SoftSerial.available()) // Lit toutes les valeurs restantes
          {
            SoftSerial.read(); // Permet de reset les valeurs de "SoftSerial"
          }
        }
      }
    }
  }
  else if (error_GPS && timeout)
  {
    int lastState = state;
    ChangeLEDStatus(erreur_GPS);
    timeout = false;
    ChangeLEDStatus(lastState);
  }
  else
  {
    gps += "NA";
  }
  SoftSerial.end();
  return gps;
}

String getLight()
{
  String clight("L:");
  if (EEPROM.read(lum_addr)) // Si capteur de luminosité activé
  {
    uint16_t luminosite = analogRead(LightSensor_Pin);
    uint16_t lumin_low;
    uint16_t lumin_high;
    EEPROM.get(lum_addr + 1, lumin_low);
    EEPROM.get(lum_addr + 3, lumin_high);
    if (lumin_low > luminosite)
    {
      clight += "faible";
    }
    else if (lumin_high < luminosite)
    {
      clight += "forte";
    }
    else
    {
      clight += "moyenne";
    }
  }else{
    clight += "Désactivé|";
  }
  return clight;
}

String getBME()
{
  float pression, temperature, hygrometrie;
  String cpres("P:");
  String ctemp("T:");
  String chygr("H:");
  String data("");
  bme.takeForcedMeasurement();
  if (EEPROM.read(pression_addr)) // Si capteur de pression activé
  {
    pression = bme.getPressure(); // Le capteur est lit en Pa, on converti en HPa
    uint16_t pressure_min;
    uint16_t pressure_max;
    EEPROM.get(pression_addr + 1, pressure_min);
    EEPROM.get(pression_addr + 3, pressure_max);
    if (pressure_min > pression || pression > pressure_max)
    {
      ChangeLEDStatus(erreur_DATA);
    }
    cpres += String(pression);
  }
  if (EEPROM.read(temp_addr)) // Si capteur de temperature activé
  {
    temperature = bme.getTemperatureCelcius(); // °C
    int8_t temp_min = EEPROM.read(temp_addr + 1);
    int8_t temp_max = EEPROM.read(temp_addr + 2);
    if (temp_min > temperature || temperature > temp_max)
    {
      ChangeLEDStatus(erreur_DATA);
    }
    ctemp += String(temperature);
  }
  if (EEPROM.read(hygro_addr)) // Si capteur d'hygrométrie activé
  {
    hygrometrie = bme.getRelativeHumidity(); // %
    int8_t hygr_min = EEPROM.read(hygro_addr + 1);
    int8_t hygr_max = EEPROM.read(hygro_addr + 2);
    if (hygr_min > hygrometrie || hygrometrie > hygr_max)
    {
      chygr += "NA";
    }else{
      chygr += String(hygrometrie);
    }
  }
  data += cpres;
  data += ctemp;
  data += chygr;
  return data;
}