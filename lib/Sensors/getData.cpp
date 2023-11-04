#include "Sensors.h"
#include <EEPROM.h>


String getDate(){
  static bool timeout = false;
  char date[] = "T : ";
  char buffer [10];
  bool error_rtc = RTC_error();
  if (!error_rtc)
  {
    strcat(date,itoa(clock.now().year(),buffer,10));
    strcat(date,"/");
    strcat(date,itoa(clock.now().month(),buffer,10));
    strcat(date,"/");
    strcat(date,itoa(clock.now().day(),buffer,10));
    strcat(date," ");
    strcat(date,itoa(clock.now().hour(),buffer,10));
    strcat(date,":");
    strcat(date,itoa(clock.now().minute(),buffer,10));
    strcat(date,":");
    strcat(date,itoa(clock.now().second(),buffer,10));
    strcat(date," | ");
    return String(date);
  }else if (error_rtc && timeout){
    int lastState = state;
    ChangeLEDStatus(erreur_RTC);
    timeout = false;
    ChangeLEDStatus(lastState);
  }else{
    strcat(date, "NA |");
    return String(date);
  }
}

String getGPS()
{
  String gps("G : ");
  static bool timeout = false;
  bool error_GPS = GPS_error();
  if (!error_GPS)
  {
    if (SoftSerial.available()) // Si il y a des valeurs a lire
    {
      int cond = 2;
      char tmp;      // caractère temporaire     String gps = "G";(à ajouter au string ou facilite la lecture)
      while (cond > 0) // Premiere boucle, on attend d'obtenir les coordonnées (après 2 virgules)
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
    return gps;
  }
  return gps;
}

String getLight()
{
  String clight("L : ");
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
    clight += " | ";
    return clight;
  }
  clight += "Désactivé | ";
  return clight;
}

String getBME()
{
  float pression, temperature, hygrometrie;
  String cpres("P : ");
  String ctemp("T : ");
  String chygr("H : ");
  String data("");
  static bool timeout = false;
  bme.takeForcedMeasurement();
    if (EEPROM.read(pression_addr)) // Si capteur de pression activé
    {
      pression = bme.getPressure() / 100; // Le capteur est lit en Pa, on converti en HPa
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
      int8_t temp_min;
      int8_t temp_max;
      EEPROM.get(temp_addr + 1, temp_min);
      EEPROM.get(temp_addr + 3, temp_max);
      if (temp_min > temperature || temperature > temp_max)
      {
        ChangeLEDStatus(erreur_DATA);
      }
      ctemp += String(temperature);
    }
    if (EEPROM.read(hygro_addr)) // Si capteur d'hygrométrie activé
    {
      hygrometrie = bme.getRelativeHumidity(); // %
      int8_t hygr_min;
      int8_t hygr_max;
      EEPROM.get(hygro_addr + 1, hygr_min);
      EEPROM.get(hygro_addr + 3, hygr_max);
      if (hygr_min > hygrometrie || hygrometrie > hygr_max)
      {
        chygr += "NA";
        data += cpres;
        data += " | ";
        data += ctemp;
        data += " | ";
        data += chygr;
        data += " | ";
        return data;
      }
      chygr += String(hygrometrie);
    }
  data += cpres;
  data += " | ";
  data += ctemp;
  data += " | ";
  data += chygr;
  data += " | ";
  return data;
}