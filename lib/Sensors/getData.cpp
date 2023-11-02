#include "Sensors.h"

String getDate(){
  static bool timeout = false;
  if (!RTC_error())
  {
    return "T : " + String(clock.now().year()) + "/" + String(clock.now().month()) + "/" + String(clock.now().day()) + " " + String(clock.now().hour()) + ":" + String(clock.now().minute()) + ":" + String(clock.now().second()) + " | ";
  }else if (RTC_error() && timeout){
    int lastState = state;
    state = erreur_RTC;
    ChangeLEDStatus();
    timeout = false;
    state = lastState;
  }else{
    return "T : NA | ";
  }
  
}

String getGPS()
{
  String gps = "G : ";
  static bool timeout = false;
  if (!GPS_error())
  {
    if (SoftSerial.available()) // Si il y a des valeurs a lire
    {
      int cond = 2;
      String tmp;      // caractère temporaire     String gps = "G";(à ajouter au string ou facilite la lecture)
      while (cond > 0) // Premiere boucle, on attend d'obtenir les coordonnées (après 2 virgules)
      {
        tmp = char(SoftSerial.read()); // Lit un caractère ASCII de SoftSerial et le convertit
        if (tmp == ",")                // Quand on voit une virgule
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
        if (tmp == "E" or tmp == "W")  // Quand on voit un E ou un W
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
  else if (GPS_error() && timeout)
  {
    int lastState = state;
    state = erreur_GPS;
    ChangeLEDStatus();
    timeout = false;
    state = lastState;
  }
  else
  {
    return "G : NA";
  }
  return gps;
}

String getLight()
{
  String clight;
  if (EEPROM.read(lum_addr)) // Si capteur de luminosité activé
  {
    int luminosite = analogRead(LightSensor_Pin);
    uint16_t lumin_low;
    uint16_t lumin_high;
    EEPROM.get(lum_addr + 1, lumin_low);
    EEPROM.get(lum_addr + 3, lumin_high);
    if (lumin_low > luminosite)
    {
      clight = "faible";
    }
    else if (lumin_high < luminosite)
    {
      clight = "forte";
    }
    else
    {
      clight = "moyenne";
    }
    return "L : " + clight + " | ";
  }
  return "L : Désactivé | ";
}

String getBME()
{
  float pression, temperature, hygrometrie;
  String cpres = "NA";
  String ctemp = "NA";
  String chygr = "NA";
  static bool timeout = false;

  if (!BME_error())
  {
    if (EEPROM.read(pression_addr)) // Si capteur de pression activé
    {
      pression = bme.pres() / 100; // Le capteur est lit en Pa, on converti en HPa
      uint16_t pressure_min;
      uint16_t pressure_max;
      EEPROM.get(pression_addr + 1, pressure_min);
      EEPROM.get(pression_addr + 3, pressure_max);
      if (pressure_min > pression || pression > pressure_max)
      {
        int lastState = state;
        state = erreur_DATA;
        ChangeLEDStatus();
        state = lastState;
        return "P : " + cpres + " | T : " + ctemp + " | H : " + chygr + " | ";
      }
      cpres = String(pression);
    }
    if (EEPROM.read(temp_addr)) // Si capteur de temperature activé
    {
      temperature = bme.temp(); // °C
      int8_t temp_min;
      int8_t temp_max;
      EEPROM.get(temp_addr + 1, temp_min);
      EEPROM.get(temp_addr + 3, temp_max);
      if (temp_min > temperature || temperature > temp_max)
      {
        int lastState = state;
        state = erreur_DATA;
        ChangeLEDStatus();
        state = lastState;
        return "P : " + cpres + " | T : " + ctemp + " | H : " + chygr + " | ";
      }
      ctemp = String(temperature);
    }
    if (EEPROM.read(hygro_addr)) // Si capteur d'hygrométrie activé
    {
      hygrometrie = bme.hum(); // %
      int8_t hygr_min;
      int8_t hygr_max;
      EEPROM.get(hygro_addr + 1, hygr_min);
      EEPROM.get(hygro_addr + 3, hygr_max);
      if (hygr_min > hygrometrie || hygrometrie > hygr_max)
      {
        return "P : " + cpres + " | T : " + ctemp + " | H : " + chygr + " | ";
      }
      chygr = String(hygrometrie);
    }
  }
  else if (BME_error() && timeout)
  {
    int lastState = state;
    state = erreur_BME;
    ChangeLEDStatus();
    timeout = false;
    state = lastState;
  }
  return "P : " + cpres + " | T : " + ctemp + " | H : " + chygr + " | ";
}