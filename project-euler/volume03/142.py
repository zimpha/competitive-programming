import math

def isSquare(n):
    x = int(math.sqrt(1.0 * n))
    return x * x == n

for a in xrange(1, 1000):
    for c in xrange(1, a):
        for b in xrange(1, c):
            if (a * a + b * b) % 2 == 1:
                continue
            x = (a * a + b * b) / 2
            y = (a * a - b * b) / 2
            z = c * c - x
            if z > y or z <= 0:
                continue
            if isSquare(x - z) and isSquare(y + z) and isSquare(y - z):
                print x, y, z, x + y + z
