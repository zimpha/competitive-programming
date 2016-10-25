from math import *

def is_square(n):
    m = int(sqrt(n))
    return n == m * m

def run(n):
    ret = 0
    for x in xrange(0, n):
        for y in xrange(0, n):
            cnt = (x > 0) + (y > 0) + (x + 1 < n) + (y + 1 < n)
            if not is_square(x * n + y + 1):
                continue
            if cnt == 3:
                ret += 3.0 / (n * 4 * (n - 1))
                ret += 4.0 / (n * (5 * n - 4))
            if cnt == 2:
                ret += 2.0 / (n * 4 * (n - 1))
                ret += 3.0 / (n * (5 * n - 4))
            if cnt == 4:
                ret += 4.0 / (n * 4 * (n - 1))
                ret += 5.0 / (n * (5 * n - 4))
    return "%.12f" % (ret * 0.5)

print run(5)
print run(1000)
