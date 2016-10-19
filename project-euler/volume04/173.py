from math import *

def run(n):
    r = 0
    for a in xrange(1, n):
        s = max(1, a * a - n);
        s = int(sqrt(s))
        while s * s < a * a - n:
            s += 1
        if s < a:
            if a % 2 == 1:
                r += a / 2 - s / 2
            else:
                r += (a - 1) / 2 - (s - 1) / 2
    return r

print run(100)
print run(1000000)
