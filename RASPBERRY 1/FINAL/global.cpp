#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <unistd.h>

using namespace std;

// THREAD 
#include <pthread.h>


static void *sms (void *p_data)
{
   system("cd /home/pi/TEST && sudo ./sms");
   //cout << "1" << endl;
   (void) p_data;
   return NULL;
}

static void *reception (void *p_data)
{
   system("cd /home/pi/TEST && sudo python3 receiver2.py >nul 2>nul");
   //cout << "2" << endl;
   (void) p_data;
   return NULL;
}

static void *moteur (void *p_data)
{
   system("cd /home/pi/Traitement && sudo ./traitement");
   //cout << "3" << endl;
   (void) p_data;
   return NULL;
}

static void *capteurs (void *p_data)
{
   system("cd /home/pi/CODES && sudo ./total");
   //cout << "4" << endl;
   (void) p_data;
   return NULL;
}

int main()
{   
   pthread_t ta;
   pthread_t tb;
   pthread_t tc;
   pthread_t td;

   puts ("Début du programme");

   pthread_create (&ta, NULL, sms, NULL);
   pthread_create (&tb, NULL, reception, NULL);
   pthread_create (&tc, NULL, moteur, NULL);
   pthread_create (&td, NULL, capteurs, NULL);
   
   pthread_join (ta, NULL);
   pthread_join (tb, NULL);
   pthread_join (tc, NULL);
   pthread_join (td, NULL);
    
   return 0;


}
