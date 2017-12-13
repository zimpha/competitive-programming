from fractions import *

n = int(raw_input())
a = map(int, raw_input().split(' ' ))

def gao(a, v):
    for x in a:
        v[x] = 1
    n = len(a)
    for i in xrange(n):
        for j in xrange(n):
            if i == j:
                continue
            t = []
            for k in xrange(n):
                if k == i or k == j:
                    continue
                t.append(a[k])
            t.append(0)
            t[-1] = a[i] - a[j]
            gao(t, v)
            t[-1] = a[i] + a[j]
            gao(t, v)
            t[-1] = a[i] * a[j]
            gao(t, v)
            if a[j]:
                t[-1] = a[i] / a[j]
                gao(t, v)

for mask in xrange(1 << n):
    x = []
    y = []
    for i in xrange(n):
        if (mask >> i & 1):
            x.append(Fraction(a[i], 1))
        else:
            y.append(Fraction(a[i], 1))
    sx = {}
    sy = {}
    if not len(x) or not len(y):
        continue
    if n >= 6 and min(len(x), len(y)) <= 2:
        continue
    gao(x, sx)
    gao(y, sy)
    for v in sx:
        if v in sy:
            print 'YES'
            exit(0)
print 'NO'
