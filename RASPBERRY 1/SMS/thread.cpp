/* ATTENTION CODE ERRONE */

#include <stdio.h>
#include <iostream>
#include <pthread.h>

static void *task_a (void *p_data)
{
   system("./sms");
   (void) p_data;
   return NULL;
}

static void *task_b (void *p_data)
{
   system("python3 receiver2.py 2>nul >nul");
   (void) p_data;
   return NULL;
}

int main (void)
{
   pthread_t ta;
   pthread_t tb;

   puts ("Début du programme");

   pthread_create (&ta, NULL, task_a, NULL);
   pthread_create (&tb, NULL, task_b, NULL);

   puts ("main end");

   return 0;
}
