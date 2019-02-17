# radar-mapper

### En français
_Radar-mapper_ est un robot, composé de deux moteurs 6V pour la propulsion commandés par un contrôleur [L298N](http://wiki.seeedstudio.com/Motor_Shield_V1.0/).
Quatre [capteurs à ultrasons](https://www.seeedstudio.com/Grove-Ultrasonic-Ranger-p-960.html) sont fixés sur une plaque, elle même fixée sur un servomoteur qui fait des allers-retours. (0-180°)

La carte arduino envoie les mesures prises sous la forme: `50,80,45,115`

Équivalent à: `position x du robot, position y du robot, angle de la mesure, distance mesurée`

La carte arduino prendra en compte l'angle que le robot a par rapport à sa position de départ ainsi que la distance parcourue depuis l'endroit où il s'est allumé.

Les mesures sont envoyées avec un [shield wifi](http://wiki.seeedstudio.com/Wifi_Shield_V2.0/) à un [serveur](http://hellow.alwaysdata.net/radar-mapper) qui génère la carte de l'environnement avec le script python [radar.py](https://github.com/Hell0w/radar-mapper/blob/master/radar.py).

Les coordonnées d'un point à partir de sa mesure sont calculées comme ceci:
```python
    X_point = distance_mesuree * cos(angle_mesure) + X_robot
    Y_point = distance_mesuree * sin(angle_mesure) + Y_robot
```
Les points sont générés sur 9 images qui sont assemblées ensemble pour créer une grande carte.
