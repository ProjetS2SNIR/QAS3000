#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <unistd.h>

using namespace std;

// THREAD 
#include <pthread.h>


static void *ils (void *p_data)
{
   system("cd /home/pi/ILS && sudo ./ils");
   //cout << "1" << endl;
   (void) p_data;
   return NULL;
}

static void *reception (void *p_data)
{
   system("cd /home/pi/MOTEUR/RECEPTION && sudo python3 reception_moteur.py >nul 2>nul");
   //cout << "2" << endl;
   (void) p_data;
   return NULL;
}

static void *moteur (void *p_data)
{
   system("cd /home/pi/MOTEUR && sudo ./moteur");
   //cout << "3" << endl;
   (void) p_data;
   return NULL;
}

int main()
{   
   pthread_t ta;
   pthread_t tb;
   pthread_t tc;

   puts ("Début du programme");

   pthread_create (&ta, NULL, ils, NULL);
   pthread_create (&tb, NULL, reception, NULL);
   pthread_create (&tc, NULL, moteur, NULL);
   
   pthread_join (ta, NULL);
   pthread_join (tb, NULL);
   pthread_join (tc, NULL);
    
   return 0;


}

