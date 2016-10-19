from math import *

def run(n):
    N = [0] * 11
    r = [0] * n
    for a in xrange(1, n):
        s = max(1, a * a - n);
        s = int(sqrt(s))
        while s * s < a * a - n:
            s += 1
        if a % 2 != s % 2:
            s += 1
        for b in xrange(s, a, 2):
            r[a * a - b * b - 1] += 1
    for i in xrange(n):
        if r[i] <= 10 and r[i] > 0:
            N[r[i] - 1] += 1
    return N

print sum(run(1000000))
