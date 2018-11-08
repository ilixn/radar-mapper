import serial
import math
from PIL import Image, ImageDraw

ser = serial.Serial('/dev/ttyUSB0', 9600) #Port of the arduino

#Open image to add obstacle points
source_img = Image.open("test.jpg")

draw = ImageDraw.Draw(source_img)

while 1:
	measurement = ser.readline() #Example: 60, 100 = degree, cm

	degree, distance = measurement.split(', ')
	
	#string --> int conversion
	degree = int(degree)
	distance = int(distance)

	#Coordonnées de l'obstacle
	ypos = float(math.sin(degree*math.pi/180)*distance) #for y
	xpos = float(math.cos(degree*math.pi/180)*distance) #for x

	print("x: " + str(xpos) + " | y: " + str(ypos)) #On affiche une ligne donnant la position de l'objet x/y

	#les coordonnées pour le dessin (l'image) qui fait 600*600px
	xprint = xpos + 300
	yprint = 300 - ypos

	#Point de 10*10px pour représenter la mesure

	draw.rectangle([xprint - 5, yprint - 5, xprint + 5, yprint + 5], fill="black") # [x0, y0, x1, y1]

	#Finalement, on sauvegarde l'image
	source_img.save("test.jpg", "JPEG")
