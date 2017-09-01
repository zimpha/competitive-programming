def is_prime(n):
    return True
    if n < 2:
        return False
    if n <= 3:
        return True
    if n % 2 == 0:
        return False
    for i in xrange(3, n, 2):
        if n % i == 0:
            return False
    return True

def gen1(x, d):
    n = x ** 2 + d
    r = []
    for y in xrange(1, n + 1):
        if n % y == 0:
            r.append((x, y, n / y))
    return r

def gen2(d):
    r = []
    for x in xrange(0, d):
        t = gen1(x, d)
        for x in t:
            r.append(x)
    mark = {}
    for x in r:
        mark[x] = 1
    for e in r:
        x, y, z = e
        mark[(x + y, y, 2 * x + y + z)] = 0
        mark[(x + z, 2 * x + y + z, z)] = 0
    cnt = 0
    for x in r:
        if mark[x] == 1:
            cnt += 1
            continue
            print x,
    if is_prime(d):
        print (cnt + 1) / 2
    print ''
    return cnt

r = [0] * 100
for i in xrange(1, 101):
    print '%d: ' % i,
    r[i - 1] = gen2(i)
for i in xrange(1, 101):
    n = i
    f = []
    p = 2
    while p * p <= n:
        if n % p == 0:
            s = 1
            while n % p == 0:
                n /= p
                s *= p
            f.append(s)
        p += 1
    if n > 1:
        f.append(n)
    v = 1
    for x in f:
        v *= r[x - 1]
    if v != r[i - 1]:
        continue
        print f, i, r[i - 1], v
