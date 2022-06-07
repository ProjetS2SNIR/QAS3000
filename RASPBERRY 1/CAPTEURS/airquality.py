#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# The MIT License (MIT)
#
# Grove Base Hat for the Raspberry Pi, used to connect grove sensors.
# Copyright (C) 2018  Seeed Technology Co.,Ltd.
'''
This is the code for
    - `Grove -  Air Quality Sensor <https://www.seeedstudio.com/Grove-Air-quality-sensor-v1.3-p-2439.html)>`_

Examples:

    .. code-block:: python

        import time
        from grove.grove_air_quality_sensor_v1_3 import GroveAirQualitySensor

        # connect to alalog pin 2(slot A2)
        PIN = 2

        sensor = GroveAirQualitySensor(pin)

        print('Detecting ...') 
        while True:
            value = sensor.value        
            if value > 100:
                print("{}, High Pollution.".format(value))
            else:
                print("{}, Air Quality OK.".format(value))
            time.sleep(.1)
'''
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
        print(value, "   l'air est pollué   ")
    else: # sinon afficher l'air est sain
        print(value, "   l'air est sain   ")


if __name__ == '__main__': #Fonction permettant d'éxecuter le main
    main()


