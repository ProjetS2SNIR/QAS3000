#include "scenarioSMS.h"
void scenarioSMS::open()
{
  cout << "\033[1;32mopen  \033[0m"; 
}

void scenarioSMS::close()
{
  cout << "\033[1;31mclose\033[0m" << endl;
}

void scenarioSMS::attendre()
{
  cout << "\033[0;33mOn attend le gardien pour qu'il la ferme \033[0m" << endl;
}

void scenarioSMS::traitement()
{
int n=0;
while(1)
{
  horaires ljj;
  reception_433 fenetre;
  string lycee = ljj.etat;
  string etat = fenetre.etat_fenetre();
    
    if (etat == "close") // On fait rien c'est fermé
    {
        close();
        n=0;
    }
    if (etat == "open" && n==1 && lycee=="fermé") // On attend le gardien
    {
        open();
        attendre();
    }
    if (etat == "open" && n==0 && lycee=="fermé") // On informe le gardien
    {
        open();
        envoiSMS();
        n=1;
    }
    if (etat == "open" && lycee=="ouvert") // On informe le gardien
    {
        open();
        etabli_ouvert();
    }
    
    sleep(5);
  }

}

void scenarioSMS::envoiSMS() { 
	sim7600.PowerOn(POWERKEY);
	printf("Sending Short Message Test:\n");
	sim7600.SendingShortMessage(phone_number,message);
	printf("Receiving Short Message Test:\n");
	printf("Please send message to phone %s.\n", phone_number);
	sim7600.ReceivingShortMessage();
}

void scenarioSMS::etabli_ouvert()
{
  cout << "\033[0;33mL'établissement est ouvert \033[0m" << endl;
}
