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
   system("sudo ./traitement");
   (void) p_data;
   return NULL;
}

static void *reception (void *p_data)
{
   system("python3 receiver2.py 2>nul >nul");
   (void) p_data;
   return NULL;
}

static void *traitement (void *p_data)
{
   system("python3 receiver2.py 2>nul >nul");
   (void) p_data;
   return NULL;
}

int main()
{   
   pthread_t ta;
   pthread_t tb;

   puts ("Début du programme");

   pthread_create (&ta, NULL, sms, NULL);
   pthread_create (&tb, NULL, reception, NULL);

   return 0;


}