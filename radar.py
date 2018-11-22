# -*- coding: utf-8 -*-

import serial
import math
from PIL import Image, ImageDraw

ser = serial.Serial('/dev/ttyUSB0', 9600) #Le port de l'arduino (linux)
image_x, image_y = 0,0

while 1: # Boucle infinie
	measurement = ser.readline() #Exemple: -1, 0, 60, 100 = x, y, degree, cm
	#measurement = str(input()) #(Pour tester)
	print(measurement)
	
	
	#------Obtention des Mesures que l'arduino a envoyées
	robot_x, robot_y, degree, distance = list(map(int, measurement.split(", "))) # "0, 0, 60, 100" --> robot_x = 0, robot_y = 0, degree = 60, distance = 100

	if degree == 180:
		degree = 181 #Quand l'angle est à 180, ça renvoie un truc bizarre


	#------Détermination des coordonnées de l'obstacle par rapport au robot
	ypos = float(math.sin(degree*math.pi/180)*distance) #for y
	xpos = float(math.cos(degree*math.pi/180)*distance) #for x

	print("Par rapport au robot: x: " + str(xpos) + " | y: " + str(ypos)) #On affiche une ligne d'information donnant la position de l'objet x/y

	#------Calcul des position absolues (depuis le point où le robot a commencé):
	xpos = xpos + robot_x
	ypos = ypos + robot_y
	print("Position finale: x: " + str(xpos) + " | y: " + str(ypos))
	

	#------Détermination de l'image sur laquelle on doit dessiner
	#On teste si le point à dessiner se trouve hors de 
	#l'image actuellement "sélectionnée" (désignée par image_x et image_y)
	#L'opération est réalisée plusieurs fois au cas où l'on devrait changer de plus d'une image.
	recommencer = 1
	while (recommencer==1):
		recommencer = 0
		if xpos > image_x * 600 + 300:
			image_x += 1
			#Chaque image fait 600px de large donc par exemple le centre de 
			#l'image directement à droite de celle du centre et donc de coordonnées (1,0) se situe en (600,0)
			#Le bord de l'image est situé à 300px de plus, ce qui donne 1*600+300
			recommencer = 1

		if xpos < image_x * 600 - 300:
			image_x -= 1
			recommencer = 1

		if ypos > image_y * 600 + 300:
			image_y += 1
			recommencer = 1

		if ypos < image_y * 600 - 300:
			image_y -= 1
			recommencer = 1

	#On détermine les coordonnées par raport au centre de l'image qu'on vient de déterminer.
	xpos = xpos - (image_x*600)
	ypos = ypos - (image_y*600)
	
	#------Détermination des coordonnées sur l'image
	#les coordonnées pour le dessin (l'image) qui fait 600*600px
	#Dans l'image (0,0) est en haut à gauche et x --> droite et y --> bas
	#On veut (0,0) au centre et x --> droite et y --> haut
	xprint = xpos + 300
	yprint = 300 - ypos

	#------Sauvegarde de l'image
	save(image_x, image_y, xprint, yprint)
		
def save(draw_x, draw_y, point_x, point_y):
	#Ouverture de l'image pour y dessiner
	try:
		image = Image.open("map_" + str(draw_x) + "," + str(draw_y) + ".jpg")
	except:
		image = Image.new('1', (600, 600), "white")

	#Pour pouvoir dessiner plus tard
	draw = ImageDraw.Draw(image)
	
	#Point de 10*10px pour représenter la mesure
	draw.rectangle([point_x - 5, point_y - 5, point_x + 5, point_y + 5], fill="black") # [x0, y0, x1, y1]
	
	#On dit ce qu'on a fait
	print("Position imprimée: x: " + str(point_x) + " | y: " + str(point_y) + " | Image: " + str(draw_x) + ", " + str(draw_y))
	print("---------------")
	
	image.save("map_" + str(draw_x) + "," + str(draw_y) + ".jpg")
	
	
