from decimal import *
fac = [1] * 101
for i in xrange(1, 101):
    fac[i] = i * fac[i - 1]

cache = {}

def C(n, m):
    return fac[n] / fac[n - m] / fac[m]

def f(n, m):
    if (n, m) in cache:
        return cache[(n, m)]
    ret = fac[n]
    for k in xrange(1, m + 1):
        ret -= C(m, k) * f(n - k, m - k)
    cache[(n, m)] = ret
    return ret

getcontext().prec = 12
print Decimal(C(25, 3) * f(75 + 22, 22)) / Decimal(fac[100])
