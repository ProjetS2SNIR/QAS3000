import time, sys
from grove.adc import ADC 

__all__ = ["GroveAirQualitySensor"]

class GroveAirQualitySensor(object):
    
def __init__(self, channel): #numéro de la branche de la broche auquel le capteur est connecté
        self.channel = channel
        self.adc = ADC()

    @property
    def value(self):
        return self.adc.read(self.channel) #renvoie la valeur de la qualité de l'air

def main():
    from grove.helper import SlotHelper 
    sh = SlotHelper(SlotHelper.ADC) #La fonction sert à connecter le capteur airqualitysensor à la raspberry en ADC 
    pin = sh.argv2pin() #La fonction permet de se connecter à la pin  

    sensor = GroveAirQualitySensor(pin)

    value = sensor.value
    if value > 150: #si la valeur est supréireur à 150 affiché l'air est polluée
        print(value, "l'air est pollué")
    else: # sinon afficher l'air est sain

if __name__ == '__main__': #Fonction permettant d'éxecuter le main
    main()
   

 
 
