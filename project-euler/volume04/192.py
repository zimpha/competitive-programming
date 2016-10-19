import math

def allow_half(c, k):
    s = 1
    for i in xrange(k, 0, -1):
        diff = s * (c[i] - c[k * 2 - i])
        if diff > 0:
            return True
        if diff < 0:
            return False
        s *= -1
    return (k - 1) % 2 != 0

def approx(n, upp):
    sn = int(math.sqrt(n) + 0.5)
    if sn * sn > n:
        sn -= 1
    if sn * sn == n:
        return 0
    a, b = 0, 1
    c = []
    for i in xrange(200):
        c.append((a + sn) / b)
        a = b * c[-1] - a
        b = (n - a * a) / b
    h = [1, 0, 1]
    k = [0, 1, c[0]]
    for i in xrange(1, 100000):
        w = c[i]
        low = (w + 1) / 2
        if w % 2 == 0 and not allow_half(c, i):
            low += 1
        x, y = 0, 0
        for e in xrange(low, w + 1):
            x = e * h[-1] + h[-2]
            y = e * k[-1] + k[-2]
            if x > upp:
                if e == low:
                    return h[-1]
                else:
                    return h[-2] + (e - 1) * h[-1]
        h.append(x)
        k.append(y)

def run(upp):
    ret = 0
    for n in xrange(1, 100001):
        ret += approx(n, upp)
    return ret

print approx(13, 20)
print approx(13, 30)
print run(10 ** 12)
