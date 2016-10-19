def f(x):
    r = int(2 ** (30.403243784 - x * x))
    return r * 10 ** -9

u = -1
for i in xrange(10000):
    u = f(u)

print u + f(u)
