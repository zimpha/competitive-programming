s = 0
for n in xrange(1, 2018):
    x = 8
    y = 0
    z = 0
    for i in xrange(n + 1):
        x = x * 10 + 1
    for i in xrange(n):
        y = y * 10 + 7
        z = z * 10 + 1
    t = z * 10 ** (n * 2 + 3) + y * 10 ** (n + 2) + x
    t /= 3
    y = 10 ** (len(str(t)) / 3)
    for i in xrange(200):
        y = (2 * y + t / y ** 2) / 3
    '''
    l, r = 1, t
    while l < r:
        m = (l + r + 1) / 2
        if m ** 3 <= t:
            l = m
        else:
            r = m - 1
    print r ** 3, y ** 3, t
    '''
    s += y
    s %= 10 ** 9 + 7
print s
