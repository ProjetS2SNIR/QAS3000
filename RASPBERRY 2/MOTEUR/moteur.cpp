#include <wiringPiI2C.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "moteur.h"

#include "RECEPTION/reception_433.cpp"


int main(){
        Moteur instanceI2C;
	reception_433 moteur;
        while(1){
	if( moteur.command() == "close") // 9900
	{
        cout << "fermeture";
	instanceI2C.close();
	}

	if(moteur.command() == "open") // 9911
	{
        cout << "ouverture";
        instanceI2C.open();
	}

	if(moteur.command() == "wait") // 9966
	{
		cout << "on fait rien " << endl;
		sleep(5);
	}
	}
}

