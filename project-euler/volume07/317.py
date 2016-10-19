from math import pi
v, h, g = 20, 100, 9.81

print pi * (2 * g * v * h + v * v * v) ** 2 / (4 * g ** 3)
