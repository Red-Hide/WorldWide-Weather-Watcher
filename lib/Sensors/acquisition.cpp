#include "Sensors.h"

String acquisition()
{
    static bool GPS_checked_before = false;
    String data_line("");
    data_line += getDate();
    data_line += getBME();
    data_line += getLight();
    switch (state){
        case economique:
            if (GPS_checked_before) 
            {
                GPS_checked_before = false;
                data_line += F("G : ECO");
            }
            else 
            {
                GPS_checked_before = true;
                data_line += getGPS();
            }
        default :
            data_line += getGPS();
    }
    //Ligne de mesure : D : + (date)  + T : + (Temperature) + H : + (Humidite) + P : + (Pression) + L : + (luminosite) + G : + (Position)
    return data_line;
}
