# -*- coding: utf-8 -*-

import sys
import math
from PIL import Image, ImageDraw
import serial


image_x, image_y = 0,0
save_image_counter = 0
adresse_arduino = '/dev/ttyACM0'

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
	print("-------OK------")

	#------Sauvegarde de l'image
	global save_image_counter
	if(save_image_counter == 10):
		image.save("map_" + str(draw_x) + "," + str(draw_y) + ".jpg")
		save_image_counter = 0
	else:
		save_image_counter += 1


def draw_image(measurement):
	print(measurement)
	global image_x
	global image_y


	#------Obtention des Mesures que l'arduino a envoyées
	try:
		robot_x, robot_y, degree, distance = list(map(int, measurement.split(","))) # "0, 0, 60, 100" --> robot_x = 0, robot_y = 0, degree = 60, distance = 100
	except:
		return
	distance = distance*3
	degree = degree * 330 / 360
	if distance < 6:
		return

	if degree == 180:
		degree = 181 #Quand l'angle est à 180, ça renvoie un truc bizarre


	#------Détermination des coordonnées de l'obstacle par rapport au robot
	ypos = float(math.sin(degree*math.pi/180)*distance) #for y
	xpos = float(math.cos(degree*math.pi/180)*distance) #for x

	print("Par rapport au robot: x: " + str(xpos) + " | y: " + str(ypos)) #On affiche une ligne d'information donnant la position de l'objet x/y


	#------Calcul des positions absolues (depuis le point où le robot a commencé):
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
			#l'image directement à droite de celle du centre (et donc de coordonnées (1,0)) se situe en (600,0)
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

#(Le code exécuté au début)

ser = serial.Serial(adresse_arduino, 9600)

while 1:
	#On sépare les mesures envoyées, séparées par des points (".")
	try:
		mesures = ser.readline().split(".")
	except:
		print("Ooops! That's a failure")
		sys.exit()

	for m in mesures:
		draw_image(m) #Boucle sur toutes les mesures
