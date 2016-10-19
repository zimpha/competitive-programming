m = 400
a = [1] * (m + 1)
for i in xrange(3, m + 1):
    a[i] = a[i - 1] + a[i - 3]

def w(n):
    n = n * a[m / 2]
    ret = 0
    i = m
    while i >= 0:
        if a[i] <= n:
            n -= a[i]
            i -= 3
            ret += 1
        else:
            i -= 1
    return ret

def run(n):
    ret = 0
    for i in xrange(n):
        ret += w((i + 1) ** 2)
    return ret

print run(10)
print run(1000)
print run(5000000)
