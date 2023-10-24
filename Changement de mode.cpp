#include <TimerOne.h>

//Permet de savoir dans quel mode retourner (standard/eco) ...
//quand on sort du mode maintenance
void setup()
{
attachInterrupt(digitalPinToInterrupt(2),Interruption_boutonV,RISING);
attachInterrupt(digitalPinToInterrupt(3),Interruption_boutonR,RISING);
Timer1.initialize(5000000);
}

void Interruption_boutonV() 
{
  //voir si cette instruction est necessaire
  //c-à-d si il faut desactiver l'interrupt pour en lancer une autre
  Timer1.detachInterrupt(); 
  Timer1.attachInterrupt(Interruption_timerV); 
}

void Interruption_timerV() 
{
  if (digitalRead(2) == 1)
  {
    //change l'etat à l'aide d'un pointeur 
    //(car on ne peut modifier une var globale dans un fct)
    switch(etat)
        case standard
          *etat = eco;
          break;
    	case eco:
          *etat = standard;
          break;
    }
  ChangeLEDSStatus(etat);
    
  }
}

void Interruption_boutonR() 
{
  //voir si cette instruction est necessaire
  //c-à-d si il faut desactiver l'interrupt pour en lancer une autre
  Timer1.detachInterrupt(); 
  Timer1.attachInterrupt(Interruption_timerR); 
}

void Interruption_timerR() 
{
static bool StandardDernierMode = 1; 
 if (digitalRead(3) == 1)
  { 
  switch etat
    case standard:
	 	*StandardDernierMode = 1;
    	*etat = maintenance;
   		break;
   case eco:
	 	*StandardDernierMode = 0;
    	*etat = maintenance;
   		break;
   case maintenance:
   		if (StandardDenierMode == 1)
        {
          *etat = standard;
   		  break;
        }
   		else
        {
          *etat = eco;
   		  break;
        }
   ChangeLEDSStatus(etat);
  } 
}