def to(n, b):
    d = []
    while n:
        d.append(str(n % b))
        n /= b
    d.reverse()
    return ''.join(d)

ret = 0
for i in xrange(1, 10000000):
    x = to(i, 4)
    y = to(i, 6)
    if x == x[::-1] and y == y[::-1]:
        ret += i
print ret
