def C(n):
    if n <= 4:
        return 2 ** (n - 1)
    r, d = 8, 5
    for i in xrange(4, n):
        r += d
        d += 1
    return r

for i in xrange(1, 20):
    print C(i)
print C(10 ** 6)
