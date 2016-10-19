# Eulerian(n, 2) \times \binom{26}{n}
def f(n):
    r = 2 ** n - n - 1
    for i in xrange(26):
        r *= (i + 1)
    for i in xrange(n):
        r /= (i + 1)
    for i in xrange(26 - n):
        r /= (i + 1)
    return r

for n in xrange(26):
    print f(n + 1)
