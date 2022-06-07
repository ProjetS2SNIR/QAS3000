// On ajoute ici les bibliothèques nécessaires au fonctionnement du programme

#include <wiringPiI2C.h> // Cette bibliothèque permet la communication avec le motorhat adafruit branché au raspberry 
#include <stdio.h>
#include <time.h>
#include <unistd.h>

// On ajouter les fichiers moteur.h et reception_433.cpp qui contiennent les classes nécessaires à ce fichier

#include "moteur.h"
#include "RECEPTION/reception_433.cpp"

// Ouverture du main

int main(){
	
	// Création des objets issu des classes crée, reception permettra la comparaison pour savoir si l'action est effectuée, et la classe Moteur permettra les actions sur le moteur 
	
        Moteur instanceI2C;
	reception_433 moteur;
        
	while(1){
	if( moteur.command() == "close") // Si moteur.command renvoie 9900 (voir programme de la récéption pour comprendre ce chiffre), on ferme la fenêtre
	{
        cout << "fermeture"; 
	instanceI2C.close(); // On envoie alors la commande close de notre objet de la classe Moteur, permettant la fermeture
	}

	if(moteur.command() == "open") // Si moteur.command renvoie 9911 (voir programme de la récéption pour comprendre ce chiffre), on ouvre la fenêtre
	{
        cout << "ouverture";
        instanceI2C.open(); // On envoie alors la commande open de notre objet de la classe Moteur, permettant l'ouverture
	}

	if(moteur.command() == "wait") // Si moteur.command renvoie 9966 (voir programme de la récéption pour comprendre ce chiffre), on ne fait rien dans ce cas la
	{
		cout << "on fait rien " << endl;
		sleep(5);
	}
	}
}

