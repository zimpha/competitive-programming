mod = 10 ** 9

def mul(a, b):
    c = []
    for i in xrange(3):
        c.append([0] * 3)
        for j in xrange(3):
            for k in xrange(3):
                c[i][j] += a[i][k] * b[k][j]
            c[i][j] %= mod
    return c

def solve(n):
    n -= 1
    r = [0, 1, 2]
    a = [[2, mod - 3, 1], [1, 0, 0], [0, 1, 0]]
    while n > 0:
        if n % 2 == 1:
            t = [0, 0, 0]
            for i in xrange(3):
                for j in xrange(3):
                    t[i] += a[i][j] * r[j]
                t[i] %= mod
            r = t
        a = mul(a, a)
        n /= 2
    return r[0]

print solve(10 ** 100)
