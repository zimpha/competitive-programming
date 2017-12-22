def summation_of_primes(n):
    def ds(n):
        return sum([int(x) for x in str(n)])

    u = int(n ** 0.5)
    ps = []
    mark = [0] * (u + 1)
    for i in xrange(2, u + 1):
        if mark[i]: continue
        ps.append(i)
        for j in xrange(i * i, u + 1, i):
            mark[j] = 1
    delta = 10 ** 6
    ret = 0
    for i in xrange(2, n + 1, delta):
        l, r = i, min(n + 1, i + delta)
        mark = [0] * (r - l)
        for p in ps:
            for x in xrange((l + p - 1) / p * p, r, p):
                mark[x - l] = 1
        for x in xrange(l, r):
            if mark[x - l]: continue
            ret += ds(x)
    for p in ps:
        ret += ds(p)
    return ret

print summation_of_primes(10 ** 9)
