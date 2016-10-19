def run(s):
    r = 0
    for n in xrange(1, s):
        for k in xrange(1, 10):
            for d in xrange(1, 10):
                m = 10 * k - 1
                rm = (pow(10, n, m) - k % m + m) * d % m
                if rm == 0:
                    s = d * (10 ** n - k) / m
                    if len(str(s)) == n:
                        r += s * 10 + d
    return r % 100000
print run(100)
