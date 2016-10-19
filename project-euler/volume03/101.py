def interpolation(x, y, n):
    u = list(y)
    r = [0] * n
    s = [0] * n
    r[0], s[0] = u[0], 1
    for i in xrange(1, n):
        for j in xrange(n - 1, i - 1, -1):
            u[j] = (u[j] - u[j - 1]) / (x[j] - x[j - i])
        for j in xrange(i, 0, -1):
            s[j] = -s[j] * x[i - 1] + s[j - 1]
            r[j] += s[j] * u[i]
        s[0] = -s[0] * x[i - 1]
        r[0] += s[0] * u[i]
    return r

def u(n):
    r = 0
    for i in xrange(11):
        if i % 2 == 0:
            r += n ** i
        else:
            r -= n ** i
    return r

x = []
y = []
ans = 0
for n in xrange(1, 12):
    x.append(n)
    y.append(u(n))
    c = interpolation(x, y, n)
    tar = u(n + 1)
    rst = 0
    for i in xrange(0, n):
        rst += c[i] * (n + 1) ** i
    print tar, rst
    if tar != rst:
        ans += rst
print ans
