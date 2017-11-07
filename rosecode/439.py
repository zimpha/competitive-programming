def pow_sum(n, k, mod):
    m = k + 3
    fac = [1] * m
    for i in xrange(2, m):
        fac[i] = i * fac[i - 1] % mod
    p = [0] * m
    for i in xrange(1, m):
        p[i] = (p[i - 1] + pow(i, k, mod)) % mod
    if n < m: return p[n]
    x = 1
    for i in xrange(1, m):
        x = x * (n - i) % mod
    ret = 0
    for i in xrange(1, m):
        iv1 = pow(fac[m - 1 - i] * fac[i - 1] % mod, mod - 2, mod)
        iv2 = pow(n - i, mod - 2, mod)
        if (m - 1 - i) % 2:
            iv1 = mod - iv1
        ret = (ret + p[i] * x * iv1 * iv2) % mod
    return ret

def kth_root(n, k):
    l, r = 1, n
    while l < r:
        m = (l + r + 1) >> 1
        if m ** k <= n: l = m
        else: r = m - 1
    return l

def S(n):
    mod = 10 ** 9 + 7
    m = len(bin(n)) - 2
    ret = [0] * m
    for k in xrange(m - 1, 2, -1):
        v = kth_root(n, k)
        ret[k] = pow_sum(v % mod, k, mod) - 1
        for j in xrange(k * 2, m, k):
            ret[k] += mod - ret[j]
        ret[k] %= mod
    return (1 + sum(ret)) % mod

print S(10 ** 2)
print S(10 ** 4)
print S(10 ** 8)
print S(10 ** 100)
