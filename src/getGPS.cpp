#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <SPI.h>

SoftwareSerial SoftSerial(4, 5);
String getGPS();

void setup() 
{
  SoftSerial.begin(9600);                 // the SoftSerial baud rate
  Serial.begin(9600);                     // the Serial port of Arduino baud rate.
}

String getGPS()
//utiliser u-center (voir https://wiki.seeedstudio.com/Grove-GPS, pour windows uniquement)
{
    String gps = "G";
    if (SoftSerial.available()) //Si il y a des valeurs a lire
    {
      int cond = 2;
      String tmp;
      while(cond > 0) //Premiere boucle, on attend d'obtenir les coordonnées (après 2 virgules)
      {
        tmp = char(SoftSerial.read());
        if (tmp == ",")
        {
          cond -= 1;
        }
       
      }
      cond = 1;
      while(cond == 1) //Tant que l'on atteint pas la fin des coordonnées (le E de est ou W de Ouest)
      {
        tmp = char(SoftSerial.read());
        gps = gps + tmp;
        if (tmp == "E" or tmp == "W")
        {
          cond = 0;
          while (SoftSerial.available()) //On lit le reste des valeurs, qui sont actuellement inutiles pour les coorodnnées
          { 
            SoftSerial.read();
          }
        }
      }
      
    }
    else
        return "GNA"; //Absence de valeurs
    return gps;
}

void loop() 
{
  Serial.println(getGPS());
  delay(5000);
}