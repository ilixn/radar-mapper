# radar-mapper
LE TPEEEE

A radar that creates a map of the environment around it

It gets the distance in every direction (degrees) and creates a map of all objects surrounding it (with cos)

Input: Robot position, degree and distance. Example: "40, 50, 60, 120". 0 < degree < 360
Output: x,y position of the object (0.86, 0.5) with x the horizontal axis (to the right) and y the vertical one (upwards)

Le robot (l'arduino) envoie sa position avec les axes toujours dans le même sens. Si il se déplace en diagonale avant droite de 1m par exemple, il enverra "70, 70" pour sa position (en cm). De même, l'arduino calcule les distances avec le 0° toujours dans la même direction. (vers la droite)

```python
math.sin(degree*math.pi/180)*distance #pour y
math.cos(degree*math.pi/180)*distance #pour x
```
