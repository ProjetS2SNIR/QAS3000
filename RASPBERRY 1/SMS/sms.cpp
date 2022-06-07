#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <unistd.h>

using namespace std;
// CONNEXION MODULE SMS 
#include "/home/pi/SIM7600X-4G-HAT-Demo/Raspberry/c/arduPi.h"

// ENVOI DU SMS
#include "/home/pi/SIM7600X-4G-HAT-Demo/Raspberry/c/sim7x00.h"

// HORAIRES ETABLISSEMENT
#include "horaires.cpp"

// RECUPERER L'ETAT DE LA FENETRE
#include "reception_433.cpp"

// TRAITEMENT & SCENARIO POUR L'ENVOI DU SMS
#include "scenarioSMS.cpp"

// THREAD 
#include <pthread.h>


int main()
{
// Je crée l'objet
   scenarioSMS action;
// Je mets en route le serveur
   action.traitement();
}


