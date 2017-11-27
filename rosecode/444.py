def S(m, n, mod):
    N = m * 2 + 10
    inv = [0] * N
    bernoulli = [1] * N
    choose = []
    for i in xrange(N):
        inv[i] = pow(i, mod - 2, mod)
        choose.append([0] * (i + 1))
        choose[i][0] = choose[i][i] = 1
        for j in xrange(1, i):
            choose[i][j] = (choose[i - 1][j] + choose[i - 1][j - 1]) % mod
    for i in xrange(1, N - 1):
        for j in xrange(i):
            bernoulli[i] -= choose[i][j] * bernoulli[j] % mod * inv[i - j + 1] % mod;
        bernoulli[i] = (bernoulli[i] % mod + mod) % mod
    powsum = [[1, 1]]
    for i in xrange(1, N - 1):
        powsum.append([0] * (i + 2))
        for k in xrange(i + 1):
            powsum[i][i + 1 - k] = inv[i + 1] * choose[i + 1][k] % mod * bernoulli[k] % mod

    def pow_sum(n, k, mod):
        if k == 0: return n % mod
        # sum_{i=1}^{n} i^k
        coef = powsum[k]
        ret, pw = 0, 1
        for i in xrange(len(coef)):
            ret += coef[i] * pw
            pw = pw * n % mod
        return ret % mod

    mem = {}
    def count(it, n, a, b, c, k, j, mod):
        # sum_{x=1}^{n} x^k * floor((ax + c) / b)^j
        # print '+', n, a, b, c, k, j
        key = (it, k, j)
        if key in mem: return mem[key]
        if n == 0:
            return 0
        if a == 0:
            return pow_sum(n, k, mod) * pow(c / b, j, mod) % mod
        if j == 0:
            return pow_sum(n, k, mod)
        if a >= b:
            q, r = divmod(a, b)
            ret, pw = 0, 1
            for i in xrange(j + 1):
                ret += choose[j][i] * pw * count(it + 1, n, r, b, c, k + i, j - i, mod) % mod
                pw = pw * q % mod
            mem[key] = ret % mod
        else:
            m = (a * n + c) / b
            ret = pow_sum(n, k, mod) * pow(m, j, mod) % mod
            for i in xrange(j):
                for h in xrange(1, k + 2):
                    ret += choose[j][i] * pow(mod - 1, j - i, mod) * powsum[k][h] % mod * count(it + 1, m, b, a, -1 - c, i, h, mod) % mod
            mem[key] = ret % mod
        return mem[key]

    ret = 0
    a = 8125651694485117498908763031637869848895468974551977284456044904
    b = 2586475266040683561385671844574761465627644563796161361121626191
    for k in xrange(1, m + 1):
        mem = {}
        ret += count(0, n, a, b * k, 0, k, k, mod)
    return ret % mod

print S(1, 10, 10 ** 9 + 7)
print S(3, 100, 10 ** 9 + 7)
print S(10, 10 ** 4, 10 ** 9 + 7)
print S(20, 10 ** 20, 10 ** 9 + 7)
