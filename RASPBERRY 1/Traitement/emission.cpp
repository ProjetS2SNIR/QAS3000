#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // pour delay 

#define MAX_LEN     512
using namespace std;

class emission {
  private:
      int gpio = 0;
      int sender = 24;
      string etat;
      int signal;
      string couleur;
      char * _date;

  public:
      void close();
      void open();
      void wait();
      void emettre();
};

void emission::emettre(){
  time_t now = time(0);
  char *_date;
  _date = ctime(&now);
  char commande[100];
  cout <<"  | commande : " << etat << "| [ " << couleur  << signal << "\033[0m ]  " << _date;
	sprintf(commande, "rpi-rf_send %d -g %d -r 50 -p 700 >nul 2>nul", signal, sender);
  sleep(1);
	system(commande);
}

void emission::close(){
    etat = "fermer  ";
    signal = 9900;
    couleur = "\033[1;31m";
    emettre();
}
void emission::open(){
    etat = "ouvrir ";
    signal = 9911;
    couleur = "\033[1;32m";
    emettre();
}

void emission::wait(){
    etat = "attendre";
    signal = 9966;
    couleur = "\033[1;33m";
    emettre();
}

