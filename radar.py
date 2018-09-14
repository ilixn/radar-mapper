import serial
import math	

ser = serial.Serial('/dev/ttyUSB0', 9600)

while 1:
	measurement = ser.readline() #60, 100 = degree, cm

	degree, distance = measurement.split(', ')
	degree = int(degree)
	distance = int(distance)

	ypos = float(math.sin(degree*math.pi/180)*distance) #for y
	xpos = float(math.cos(degree*math.pi/180)*distance) #for x

	print("x: " + str(xpos) + " | y: " str(ypos))


	xprint = xpos + 300
	yprint = 300 - ypos

	