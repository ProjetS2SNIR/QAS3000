#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // pour delay 

#define MAX_LEN     512
using namespace std;

class fenetre {
  private:
      int gpio = 0;
      int sender = 24;
      string etat;
      int signal;
      string couleur;
      char * _date;

  public:
      void configureGPIO();
      char lireGPIO();
      void emettre();
      void open();
      void close();
};


void fenetre::configureGPIO()
{
  char mode[100], write[100];
  sprintf(mode, "gpio mode %d out", gpio);
  system(mode);

  sprintf(write, "gpio write %d 1", gpio);
  system(write);
}

char fenetre::lireGPIO()
{
	char resultat, read[100];
  sprintf(read, "gpio read %d", gpio);
	FILE * f = popen(read, "r");
	char pwd[MAX_LEN] = {0};
	fgets(pwd, MAX_LEN, f);
	resultat=pwd[0]; 
	pclose(f);
  return resultat;
}

void fenetre::emettre(){
  time_t now = time(0);
  char *_date;
  _date = ctime(&now);
  char commande[100];
  cout <<"  | etat : " << etat << "| [ " << couleur  << signal << "\033[0m ]  " << _date;
	sprintf(commande, "rpi-rf_send %d -g %d -r 50 -p 700", signal, sender);
  sleep(1);
	system(commande);
}

void fenetre::close(){
    etat = "fermée  ";
    signal = 60000;
    couleur = "\033[1;31m";
}
void fenetre::open(){
		etat = "ouverte ";
    signal = 61111;
    couleur = "\033[1;32m";
}
int main() {
fenetre A036;
char read[100];
A036.configureGPIO();
char resultat={0};
char ancien;


while(1){
  resultat = A036.lireGPIO();
	if (resultat=='0' && resultat!=ancien)
	{
    A036.close();
    A036.emettre();
	}

	if (resultat=='1' && resultat!=ancien)
	{
    A036.open();
    A036.emettre();
	}
	ancien = resultat;
	}
}

