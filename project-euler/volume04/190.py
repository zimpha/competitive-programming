# x_i = i * x_1
def P(m):
    s = m * (m + 1) / 2
    a = 2 ** s;
    for i in xrange(m):
        a *= (i + 1) ** (i + 1)
    b = (m + 1) ** s
    return a / b
r = 0
for m in xrange(2, 16):
    r += P(m)
print r
