#include "Sensors.h"

String acquisition()
{
    static bool GPS_checked_before = false;
    String data_line;
    switch (state){
        case economique:
            if (GPS_checked_before) 
            {
                GPS_checked_before = false;
                data_line = getDate()  + getBME() + getLight() + "G : ECO";
            }
            else 
            {
                GPS_checked_before = true;
                data_line = getDate()  + getBME() + getLight() + getGPS();
            }
        default :
            data_line = getDate()  + getBME() + getLight() + getGPS();
    }
    //Ligne de mesure : D : + (date)  + T : + (Temperature) + H : + (Humidite) + P : + (Pression) + L : + (luminosite) + G : + (Position)
    return data_line;
}
