#include <Libraries.h>


BME280I2C bme;

String getDate();
String getGPS();
String getBME();
String getLight();

void acquision()
{
    //Ligne de mesure : D + (date) + G + (Position) + T  + (Temperature) + H + (Humidite) + P + (Pression) + L  + (luminosite)
    String LigneMesure = getDate() + getBME() + getLight();

    SDCardWrite(LigneMesure);

    //voir comment fonctionne le gps et l'heure
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


DS1307 clock; 

String getDate() {
    clock.begin(); 
    String date = "";


    Time t = clock.getTime();

    String year = String(t.year, DEC);
    String month = String(t.mon, DEC);
    String day = String(t.date, DEC);

    date = year + "/" + month + "/" + day;

    return "D" + date;
}
