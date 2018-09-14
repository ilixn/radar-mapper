# radar-mapper
A radar that creates a map of the environment around it

It gets the distance in every direction (degrees) and creates a map of all objects surrounding it (with cos)

Input: degree and distance (ex: (60°, 1m))
Output: x,y position of the object (0.86, 0.5) with x the horizontal axis and y the vertical one

```python
math.cos(degree*math.pi/180)*distance #for y
math.sin(degree*math.pi/180)*distance #for x
```
