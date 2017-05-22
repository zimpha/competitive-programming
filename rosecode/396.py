def G(n, k):
    if n <= 1:
        return n
    ret, t = 0, 0
    while n > 0:
        n, c = divmod(n, k)
        if c > 0:
            ret += c * (k + 1) ** G(t, k)
        t += 1
    return ret

r = 13
for i in xrange(2, 51):
    r = G(r, i) - 1
print r
