from sgp30 import SGP30 #Insertion de la librairie SGP30
import time
import sys

sgp30 = SGP30()

#result = sgp30.command('set_baseline', (0xFECA, 0xBEBA)) 
def crude_progress_bar():
	sys.stdout.write('.')
	sys.stdout.flush()

sgp30.start_measurement()

result = sgp30.get_air_quality()
print(result)
time.sleep(1.0)
