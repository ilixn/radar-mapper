# radar-mapper

_Radar-mapper_ est un robot, composé de deux moteurs 6V pour la propulsion commandés par un contrôleur [L298N](http://wiki.seeedstudio.com/Motor_Shield_V1.0/).
Quatre [capteurs à ultrasons](https://www.seeedstudio.com/Grove-Ultrasonic-Ranger-p-960.html) sont fixés sur une plaque, elle même fixée sur un servomoteur qui fait des allers-retours. (0-180°)

La carte arduino envoie les mesures prises sous la forme: `50,80,45,115`

Équivalent à: `position x du robot, position y du robot, angle de la mesure, distance mesurée`

La carte arduino prendra en compte l'angle que le robot a par rapport à sa position de départ ainsi que la distance parcourue depuis l'endroit où il s'est allumé.

Les mesures sont envoyées en serial (par câble) à un Raspberry Pi qui génère la carte de l'environnement avec le script python [radar.py](https://github.com/Hell0w/radar-mapper/blob/master/radar.py).

Les coordonnées d'un point à partir de sa mesure sont calculées comme ceci:
```python
    X_point = distance_mesuree * cos(angle_mesure) + X_robot
    Y_point = distance_mesuree * sin(angle_mesure) + Y_robot
```
Les points sont générés sur 9 images qui sont assemblées ensemble pour créer une grande carte.

---
:exclamation: Problèmes actuels:

- Le servomoteur ne fonctionne pas en même temps que les moteurs
- La boussole n'entre pas encore en compte dans les mesures
- Le programme de déplacement autonome n'est pas encore géré
---

### Bibliothèques:
https://github.com/Seeed-Studio/SeeedMotorShieldV2

https://github.com/Seeed-Studio/Grove_3_Axis_Compass_V2.0_BMM150
