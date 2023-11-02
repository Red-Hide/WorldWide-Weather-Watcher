#include <Libraries.h>


BME280I2C bme;

String getDate();
String getGPS();
String getBME();
String getLight();

void acquision()
{
    //Ligne de mesure : D + (date) + G + (Position) + T  + (Temperature) + H + (Humidite) + P + (Pression) + L  + (luminosite)
    String LigneMesure = String("D" + clock.now()) + getGPS() + getBME() + getLight();

    SDCardWrite(LigneMesure);

    //voir comment fonctionne le gps et l'heure
}

