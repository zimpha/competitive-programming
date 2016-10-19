import math
import sys

def gcd(a, b):
    if b == 0:
        return a
    else:
        return gcd(b, a % b)

def isSquare(n):
    x = int(math.sqrt(n))
    return x * x == n

ret = 0
upp = 10 ** 12
sol = set()
for a in xrange(2, 10000):
    for b in xrange(1, a):
        if a ** 3 * b + b * b >= upp:
            break
        if gcd(a, b) != 1:
            continue
        for c in xrange(1, sys.maxint):
            s = b * c * (c * a ** 3 + b)
            if s >= upp:
                break
            if isSquare(s) and (not s in sol):
                sol.add(s)
for x in sol:
    ret += x
print ret
