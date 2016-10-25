#A001462
m = 2 * 10 ** 7
g = [0] * m
g[1] = 1
for i in xrange(2, m):
    g[i] = 1 + g[i - g[g[i - 1]]]
ig = [0] * m
for i in xrange(1, m):
    ig[i] = ig[i - 1] + i * g[i]
    g[i] += g[i - 1]

def G(n):
    if n < m:
        return g[n] - g[n - 1]
    l, r = 1, m - 1
    while l < r:
        t = (l + r + 1) / 2
        if ig[t] < n:
            l = t
        else:
            r = t - 1
    return g[l] + (n - ig[l] + l) / (l + 1)

def run(n):
    ret = 0
    for i in xrange(1, n):
        ret += G(i ** 3)
    return ret

assert G(10 ** 3) == 86
assert G(10 ** 6) == 6137
assert run(10 ** 3) == 153506976
print run(10 ** 6)
