from math import *

eps = 1e-4
alpha, v, g = map(int, raw_input().split())
alpha = alpha * pi / 180
x, y = map(int, raw_input().split())
alpha, v, g, x, y = float(alpha), float(v), float(g), float(x), float(y)
A = 2. * v * v * sin(alpha) * cos(alpha) / g
B = - 0.5 * g / v / v / cos(alpha) / cos(alpha)
f = lambda x: B * x * x

dy = v * v * sin(alpha) * sin(alpha) / 2 / g
dx = 0.5 * A

vx = v * cos(alpha)

x -= dx
y -= dy
if abs(f(x) - y) <= eps:
	print 'Ok'
	exit(0)

if f(x) > y + eps:
	print 'Impossible'
	exit(0)

t0 = v * sin(alpha) / g

d1 = (B * x - sqrt(B * B * x * x - B * y)) / B
d2 = (B * x + sqrt(B * B * x * x - B * y)) / B
d1, d2 = min(d1, d2), max(d1, d2)
d = None
if d1 <= x:
	d = d1
if d2 <= x:
	d = d2

if d == None or d + eps <= -dx:
	print 'Impossible'
	exit(0)

print '%.20f\n' % (t0 + d / vx)
