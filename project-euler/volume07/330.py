# A(n): (mod, mod * (mod - 1))

def calc(n, mod):
    m = mod * mod
    fac = [1] * m
    for i in xrange(1, m):
        fac[i] = fac[i - 1] * i % mod
    C = [1] * m
    F = [1] * m
    A, B = [1], [1]
    for i in xrange(1, m):
        F[i] = 1
        for j in xrange(i - 1, 0, -1):
            C[j] = (C[j] + C[j - 1]) % mod
            F[j] = F[j + 1] * (j + 1) % mod
        a, b = fac[i], fac[i] + sum(F[:i])
        for j in xrange(1, i + 1):
            a += C[j] * A[i - j]
            b += C[j] * B[i - j]
        A.append(a % mod)
        B.append(b % mod)
    if n < mod:
        return (A[n] - B[n] + mod) % mod
    n -= mod
    n %= m - mod
    return (A[mod + n] - B[mod + n] + mod) % mod

def exgcd(a, b):
    if b == 0:
        return 1, 0, a
    y, x, g = exgcd(b, a % b)
    y -= x * (a / b)
    return x, y, g

def crt(c, m):
    M, ret = 1, 0
    for x in m:
        M *= x
    for i in xrange(len(c)):
        tm = M / m[i]
        x, y, g = exgcd(tm, m[i])
        ret = (ret + tm * x * c[i]) % M
    return ret

def run(n):
    mod = [7, 11, 73, 101, 137]
    res = []
    for x in mod:
        res.append(calc(n, x))
    return crt(res, mod)

print run(10)
print run(10 ** 9)
