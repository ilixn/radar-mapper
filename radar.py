# -*- coding: utf-8 -*-

import serial
import math
from PIL import Image, ImageDraw

ser = serial.Serial('/dev/ttyUSB0', 9600) #Le port de l'arduino (linux)
save=0 #variable pour compter avant de sauvegarder
image_x, image_y = 0,0

#Ouverture de l'image pour y dessiner
try:
	source_img = Image.open("test.jpg")
except:
	print("L'image n'existe pas")


draw = ImageDraw.Draw(source_img) #Pour pouvoir dessiner plus tard

while 1: # Boucle infinie
	measurement = ser.readline() #Exemple: -1, 0, 60, 100 = x, y, degree, cm
	

	#------Mesures
	robot_x, robot_y, degree, distance = list(map(int, measurement.split(", "))) # "0, 0, 60, 100" --> robot_x = 0, robot_y = 0, degree = 60, distance = 100

	if degree == 180:
		degree = 181 #Quand l'angle est à 180, ça renvoie un truc bizarre


	#------Détermination des coordonnées de l'obstacle par rapport au robot
	ypos = float(math.sin(degree*math.pi/180)*distance) #for y
	xpos = float(math.cos(degree*math.pi/180)*distance) #for x

	print("Par rapport au robot: x: " + str(xpos) + " | y: " + str(ypos)) #On affiche une ligne d'information donnant la position de l'objet x/y

	#Calcul des position absolues (depuis le point où le robot a commencé):
	xpos = xpos + robot_x
	ypos = ypos + robot_y
	print("Position finale: x: " + str(xpos) + " | y: " + str(ypos))
	

	#------Détermination de l'image sur laquelle on doit dessiner
	if xpos > image_x * 600 + 300:
		image_x += 1
		#Chaque image fait 600px de large donc par exemple le centre de 
		#l'image directement à droite de celle du centre et donc de coordonnées (1,0) se situe en (600,0)
		#Le bord de l'image est situé à 300px de plus, ce qui donne 1*600+300

	if xpos < image_x * 600 - 300:
		image_x -= 1

	if ypos > image_y * 600 + 300:
		image_y += 1

	if ypos < image_y * 600 - 300:
		image_y -= 1


	#------Détermination des coordonnées sur l'image
	#les coordonnées pour le dessin (l'image) qui fait 600*600px
	#Dans l'image (0,0) est en haut à gauche et x --> droite et y --> bas
	#On veut (0,0) au centre et x --> droite et y --> haut
	xprint = xpos + 300
	yprint = 300 - ypos

	#Point de 10*10px pour représenter la mesure
	draw.rectangle([xprint - 5, yprint - 5, xprint + 5, yprint + 5], fill="black") # [x0, y0, x1, y1]
	print("Position imprimée: x: " + str(xprint) + " | y: " + str(yprint))
	print("--------")


	#------Sauvegarde de l'image
	save = save + 1 # À chaque fois on ajoute 1, à 5 on sauvegardera
	#Finalement, on sauvegarde l'image tous les 5 points
	if save==10:
		source_img.save("test.jpg", "JPEG")
		save=0 # On réinitialise le compteur
		print("image sauvegardée")
