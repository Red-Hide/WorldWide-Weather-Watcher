//Erreur d'accès à l'horloge RTC
   while(true)
   {
    leds.setColorRGB(7, 255, 0, 0); //rouge
    delay(1000);
    leds.setColorRGB(7, 0, 0, 255); //bleu
    delay(1000);
   }

//Erreur d'accès au GPS
   while(true)
   {
    leds.setColorRGB(7, 255, 0, 0); //rouge
    delay(1000);
    leds.setColorRGB(7, 255, 255, 0); //jaune
    delay(1000);
   }

//Erreur d'accès au capteur
   while(true)
   {
    leds.setColorRGB(7, 255, 0, 0); //rouge
    delay(1000);
    leds.setColorRGB(7, 0, 255, 0); //vert
    delay(1000);
   }

//Données d'un capteur incohérente
   while(true)
   {
    leds.setColorRGB(7, 255, 0, 0); //rouge
    delay(1000);
    leds.setColorRGB(7, 0, 255, 0); //vert
    delay(2000);
   }
   
//Carte SD pleine
   while(true)
   {
    leds.setColorRGB(7, 255, 0, 0); //rouge
    delay(1000);
    leds.setColorRGB(7, 255, 255, 255); //blanc
    delay(1000);
   }

//Erreur d'ecriture/accès SD
   while(true)
   {
    leds.setColorRGB(7, 255, 0, 0); //rouge
    delay(1000);
    leds.setColorRGB(7, 255, 255, 255); //blanc
    delay(2000);
   }