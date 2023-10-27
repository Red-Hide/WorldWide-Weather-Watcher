#include <GetDate.h>
DS1307 clock; 

String getDate() {
    clock.begin(); 
    String date = "";


    clock.getTime();

    String year = String(clock.year, DEC);
    String month = String(clock.month, DEC);
    String day = String(clock.dayOfMonth, DEC);

    date = year + "/" + month + "/" + day;

    return date;
}