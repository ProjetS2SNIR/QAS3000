#include <stdio.h>
#include <time.h>

int main( int argc, char * argv[] ) {

    const char * months[] = { 
        "Janvier", "Février", "Mars", "Avril", "Mai", "Juin", "Juillet",
        "Août", "Septembre", "Octobre", "Novembre", "Décembre"
    };
    const char * days[] = {
        "Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"
    };

    time_t timestamp = time( NULL );
    struct tm * now = localtime( & timestamp );

    printf( "%4d-%02d-%02d %02d:%02d:%02d\n", 
        now->tm_year+1900, now->tm_mon+1, now->tm_mday,
        now->tm_hour, now->tm_min, now->tm_sec );
     
    printf( "Nous sommes le %s %d %s %d\n",
            days[now->tm_wday], now->tm_mday,
            months[now->tm_mon], now->tm_year+1900);
                
    return 0;
}
