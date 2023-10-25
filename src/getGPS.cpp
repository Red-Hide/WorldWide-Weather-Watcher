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
{
    String gps = "G";
    if (SoftSerial.available()) //Si il y a des valeurs a lire
    {
      int cond = 2;
      String tmp; //caractère temporaire (à ajouter au string ou facilite la lecture)
      while(cond > 0) //Premiere boucle, on attend d'obtenir les coordonnées (après 2 virgules)
      {
        tmp = char(SoftSerial.read()); //Lit un caractère ASCII de SoftSerial et le convertit
        if (tmp == ",") //Quand on voit une virgule
        {
          cond -= 1;
        }
       
      }
      //A partir de maintenant, coordonnées GPS
      cond = 1; //Reset de la condition
      while(cond == 1) //Tant que l'on atteint pas la fin des coordonnées (le E de est ou W de Ouest)
      {
        tmp = char(SoftSerial.read()); //Lit un caractère ASCII de SoftSerial et le convertit
        gps += tmp; //Ajout du caractère aux coordonnées
        if (tmp == "E" or tmp == "W") //Quand on voit un E ou un W 
        {
          cond = 0; //Fin de la boucle
          while (SoftSerial.available()) //Lit toutes les valeurs restantes
          { 
            SoftSerial.read(); //Permet de reset les valeurs de "SoftSerial"
          }
        }
      }
      
    }
    else
        return "GNA"; //Renvoie une absence de valeurs
    return gps; //Renvoie les coordonnées gps
}

void loop() 
{
  Serial.println(getGPS());
  delay(5000);
}