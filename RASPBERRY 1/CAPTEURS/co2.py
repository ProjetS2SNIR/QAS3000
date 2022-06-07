from sgp30 import SGP30 #Insertion de la librairie SGP30
import time
import sys

sgp30 = SGP30()

def crude_progress_bar(): #Fonction permettant de chauffer le capteur avant la mesure
        sys.stdout.flush()

sgp30.start_measurement() #Fonction permettant de mesurer le CO2 dans l'air

result = sgp30.get_air_quality()
print(result) #Affichage des résultats
time.sleep(1.0)
