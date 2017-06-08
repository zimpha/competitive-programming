from fractions import *

def lcm(a, b): return a * b / gcd(a, b)

for it in xrange(int(raw_input())):
    a, b, c, d = map(int, raw_input().split())
    x, y = lcm(a, c), gcd(b, d)
    g = gcd(x, y)
    print x / g, y / g
