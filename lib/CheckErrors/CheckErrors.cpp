#include <arduino.h>
#include "CheckErrors.h"

bool CheckErrorBME()
{
    static bool Erreur_BME_avant = false;
    unsigned long debut = millis() ;//verifier le type
    
    while (millis() - debut < TIMEOUT * 1000 && !bme.begin())
    {}
    if(!bme.begin())
    {
        if (Erreur_BME_avant == false)
        {
          Erreur_BME_avant = true;
          return true;
        }
        else 
        {
            while(!bme.begin())
            {
                leds.setColorRGB(7, 255, 0, 0); //rouge
                delay(1000);
                leds.setColorRGB(7, 0, 255, 0); //vert
                delay(1000);
            }
        }
    }
    else 
    {
      Erreur_BME_avant = false; 
    }
    return false;
}

//Pas d'erreur avec le capteur de lumière :
//C'est un pin analogue, il y a toujours un retour avec analogRead, même s'il n'est pas branché.


//A appeler après la lecture des données du GPS
//Permet de vérifier si on a accès à toutes les données (c'est-à-dire pas de manque, donc pas de virgules adjacentes)
String CheckErrorGPS(String gps_data)
{
  
  bool invalid = check_data_invalid(gps_data);
  while (invalid)
  {
    leds.setColorRGB(7, 255, 0, 0); //rouge
    delay(1000);
    leds.setColorRGB(7, 255, 255, 0); //jaune
    delay(1000);
    gps_data = GetGPS();
    invalid = check_data_invalid(gps_data);
  }
  return gps_data;
}

bool check_data_invalid(String gps_data)
{
  int i;
  for (i=0;i<gps_data.lenght()-1;i++)
  {
    if (gps_data[i] == ',' && gps_data[i+1] == ',')
    {
        return true;
    }
  }
  return false;
}

bool SDCard_Errors(const char *path) 
{
    if (!file.open(path)) 
    {
        state = erreur_SD;
        return true;
    }
    return false;
}

bool SDCard_Space()
{ // use card.card() to return pointer
    uint32_t totalSpace = card.blocksPerCluster() * card.clusterCount() /1024;
    uint32_t usedSpace = card.blocksPerCluster() * (card.clusterCount() - card.fatCount()) /1024;
    if (usedSpace >= totalSpace) 
    {
        state = SD_FULL;
        return true;
    }
   return false;
}