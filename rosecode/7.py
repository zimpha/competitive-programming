def to(n, b):
    d = []
    while n:
        d.append(str(n % b))
        n /= b
    d.reverse()
    return ''.join(d)

for i in xrange(1, 10000000):
    x = to(i, 8)
    y = to(int(str(i)[::-1]), 9)
    if x == y:
        print x
