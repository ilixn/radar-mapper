import serial
import math
from PIL import Image, ImageDraw

ser = serial.Serial('/dev/ttyUSB0', 9600) #Le port de l'arduino (linux)
save=0 #variable pour compter avant de sauvegarder

#On ouvre l'image pour ajouter les points représentant les obstacles
try:
	source_img = Image.open("test.jpg")
except:
	print("L'image n'existe pas")


draw = ImageDraw.Draw(source_img) #Pour pouvoir dessiner plus tard

while 1: # Boucle infinie
	measurement = ser.readline() #Exemple: 60, 100 = degree, cm

	degree, distance = measurement.split(', ') # "60, 100" --> degree = "60", distance = "100"
	
	#string --> int conversion
	degree = int(degree) # "60" --> 60
	distance = int(distance)

	#Coordonnées de l'obstacle
	ypos = float(math.sin(degree*math.pi/180)*distance) #for y
	xpos = float(math.cos(degree*math.pi/180)*distance) #for x

	print("x: " + str(xpos) + " | y: " + str(ypos)) #On affiche une ligne d'information donnant la position de l'objet x/y

	#les coordonnées pour le dessin (l'image) qui fait 600*600px
	#Dans l'image (0,0) est en haut à gauche et x --> droite et y --> bas
	#On veut (0,0) au centre et x --> droite et y --> haut
	xprint = xpos + 300
	yprint = 300 - ypos

	#Point de 10*10px pour représenter la mesure
	draw.rectangle([xprint - 5, yprint - 5, xprint + 5, yprint + 5], fill="black") # [x0, y0, x1, y1]

	save = save + 1 # À chaque fois on ajoute 1, à 5 on sauvegardera

	#Finalement, on sauvegarde l'image tous les 5 points
	if save=5:
		source_img.save("test.jpg", "JPEG")
		save=0 # On réinitialise le compteur
