import Adafruit_DHT #Insertion de la librairie Adafruit_DHT

sensor = Adafruit_DHT.DHT22 # Le capteur est réglé sur sur Adafruit_DHT.DHT22

pin = 4 # Connecté à la broche Gpio 4 

humidity, temperature = Adafruit_DHT.read_retry(sensor, pin)

   
if humidity is not None and temperature is not None:
    print('Temp={0:0.1f}°C  Humidity={1:0.1f}%'.format(temperature, humidity)) # Affichage de valeur de température et d'humidité   
else:
    print('Failed to get reading. Try again!')

