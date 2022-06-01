#!/usr/bin/env python3

import argparse
import signal
import sys
import time
import logging

from rpi_rf import RFDevice

rfdevice = None


def exithandler(signal, frame):
    rfdevice.cleanup()
    sys.exit(0)

logging.basicConfig(level=logging.INFO, datefmt='%Y-%m-%d %H:%M:%S',
                    format='%(asctime)-15s - [%(levelname)s] %(module)s: %(message)s', )

parser = argparse.ArgumentParser(description='Receives a decimal code via a 433/315MHz GPIO device')
parser.add_argument('-g', dest='gpio', type=int, default=16,
                    help="GPIO pin (Default: 16)")
args = parser.parse_args()

signal.signal(signal.SIGINT, exithandler)
rfdevice = RFDevice(args.gpio)
rfdevice.enable_rx()
timestamp = None
logging.info("Ecoute de code sur GPIO " + str(args.gpio))
while True:
    if rfdevice.rx_code_timestamp != timestamp:
        timestamp = rfdevice.rx_code_timestamp
        #logging.info(str(rfdevice.rx_code) +
        #             " [pulselength " + str(rfdevice.rx_pulselength) +
        #             ", protocol " + str(rfdevice.rx_proto) + "]")
        if rfdevice.rx_code == 9900:
          fichier = open('../command.txt', 'w+')
          fichier.write('close')
          print("\033[1;31;40m",rfdevice.rx_code)
          fichier.close()
          time.sleep(1)
        elif rfdevice.rx_code == 9911:
          fichier = open('../command.txt', 'w+')
          fichier.write('open')
          print("\033[1;32;40m",rfdevice.rx_code)
          fichier.close()
          time.sleep(1)
        
        elif rfdevice.rx_code == 9966:
          fichier = open('../command.txt', 'w+')
          fichier.write('wait')
          print("\033[1;33;40m",rfdevice.rx_code)
          fichier.close()
          time.sleep(1)
        else:
          print("\033[1;37;40m",rfdevice.rx_code)
    time.sleep(0.01)
rfdevice.cleanup()



