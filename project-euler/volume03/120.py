def f(a):
    r = 2
    for n in xrange(1, a * a, 2):
        t = 2 * n * a % (a * a)
        if t > r:
            r = t
    return r

ret = 0
for a in xrange(3, 1001):
    ret += f(a)
print ret
