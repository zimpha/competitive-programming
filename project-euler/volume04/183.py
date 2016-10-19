import math
import fractions
# P reach max, when k = n / e
def M(n):
    e = math.exp(1)
    k = round(n / e)
    k /= fractions.gcd(k, n)
    while k % 2 == 0:
        k /= 2
    while k % 5 == 0:
        k /= 5
    return k == 1

def run(n):
    r = 0
    for i in xrange(5, n + 1):
        if M(i):
            d = -i
        else:
            d = i
        r += d
    return r
print run(100)
print run(10000)
