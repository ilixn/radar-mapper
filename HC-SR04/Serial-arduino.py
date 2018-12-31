# -*- coding: utf-8 -*-
#Script pour utiliser l'arduino reliée à un ordinateur et envoyer ça au serveur

import serial
from time import sleep
import subprocess

ser = serial.Serial('/dev/ttyUSB3', 9600)

for loop in range(300):
	#print(ser.readline().strip('\r\n'))
	print subprocess.check_output(['curl', 'hellow.alwaysdata.net/radar-mapper/serve.php?coords=' + ser.readline().strip('\r\n')])
