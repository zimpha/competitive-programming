from fractions import *

def run(n):
    fib = [1] * n
    for i in xrange(2, n):
        fib[i] = (fib[i - 1] + fib[i - 2]) % 5
    f = [x + 1 for x in fib]
    for i in xrange(1, n):
        f[i] += f[i - 1]
    s = [Fraction(x, f[-1] * 2) for x in f]
    t = [x / (1 - x) for x in s]
    r = 1 / t[0]
    for i in xrange(1, n):
        r += 1 / (t[i] - t[i - 1])
    return r

print run(3)
print run(1919)
