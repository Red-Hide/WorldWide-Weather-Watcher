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