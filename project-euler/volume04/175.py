def f(n, m):
    r = []
    while m != 0:
        r.append(n / m)
        n, m = m, n % m
    r.reverse()
    r = r[:-1]
    if len(r) % 2 == 0:
        r[0] -= 1
        r.reverse()
        r.append(1)
        r.reverse()
    return r
print f(13, 17)
print f(123456789, 987654321)
