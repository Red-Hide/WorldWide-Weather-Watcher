#include "Sensors.h"

String getGPS()
{
    String gps = "G";
    if (SoftSerial.available()) //Si il y a des valeurs a lire
    {
      int cond = 2;
      String tmp; //caractère temporaire     String gps = "G";(à ajouter au string ou facilite la lecture)
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

String getLight()
{
    String clight = "NA";
    if (LUMIN) //Si capteur de luminosité activé
    {
        int luminosite = analogRead(CapteurLumiere);
        if (LUMIN_MIN > luminosite || luminosite > LUMIN_MAX)
        {
            *etat = erreur_valeur_capteur;
            return "error"; 
        }
        clight = String(luminosite);
    }
    return "L" + clight;
}

String getBME() 
{
    float pression,temperature,hygrometrie;
    String cpres = "NA";
    String ctemp = "NA";
    String chygr = "NA";

    if (PRESSURE) //Si capteur de pression activé
    {  
        pression = bme.pres()/100; //Le capteur est lit en Pa, on converti en HPa
        if (PRESSURE_MIN > pression || pression > PRESSURE_MAX)
        {
            *etat = erreur_valeur_capteur;
            return "erreur";
        }
        cpres = String(pression);
    }
    if (TEMP_AIR) //Si capteur de temperature activé
    {  
        temperature = bme.temp(); // °C
        if (TEMP_AIR_MIN > temperature || temperature > TEMP_AIR_MAX)
        {
            *etat = erreur_valeur_capteur;
            return "erreur";
        }
        ctemp = String(temperature);
    }
    if (HYGR) //Si capteur d'hygrométrie activé
    {  
        hygrometrie = bme.hum(); // %
        if (HYGR_MIN > hygrometrie || hygrometrie > HYGR_MAX)
        {
            *etat = erreur_valeur_capteur;
            return "erreur"; 
        }
        chygr = String(hygrometrie);
    }
    
    return "P" + cpres + "T" + ctemp + "H" + chygr;
}