from decimal import *

getcontext().prec = 100

def ds(n):
    c = 2
    for i in xrange(2, 11):
        c = c * (c + i + 140) / i
        s = len(str(c))
        if i == n:
            return s

    c = Decimal(c).ln()
    for n in xrange(11, n + 1):
        c = c * 2 - Decimal(n).ln()
    return int(c / Decimal(10).ln()) + 1

def solve(n):
    def rec(n, mod):
        if n == 1:
            return 2 % mod
        x = rec(n - 1, mod * n)
        return x * (x + n + 140) % (mod * n) / n
    x = rec(n - 1, n)
    return x * (x + n + 140) % n

for i in xrange(2, 1000):
    if solve(i):
        print i, ds(i)
        break

