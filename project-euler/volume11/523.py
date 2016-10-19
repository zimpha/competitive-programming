fac = [1] * 100
for i in xrange(1, 100):
    fac[i] = i * fac[i - 1]

def C(n, m):
    return fac[n] / fac[m] / fac[n - m]

def run(n):
    ret = 0
    for i in xrange(1, n + 1):
        for j in xrange(1, n + 1):
            for k in xrange(1, min(j + 1, i)):
                if k == i:
                    continue
                ret += C(j - 1, k - 1) * C(n - j, i - k) * fac[i - 1] * fac[n - i] * 2 ** (k - 1)
    return ret * 1.0 / fac[n]
print run(4)
print run(10)
print run(30)
