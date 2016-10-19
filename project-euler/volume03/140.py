# https://www.alpertron.com.ar/QUAD.HTM
# 5x^2 + 14x + 1 = y^2
# x = -9x - 4y - 14
# y = -20x - 9y - 28
st = [(0, -1), (0, 1), (-3, -2), (-3, 2), (-4, -5), (-4, 5), (2, -7), (2, 7)]
sol = []
for (x, y) in st:
    for i in xrange(30):
        x, y = -9 * x - 4 * y - 14, -20 * x - 9 * y - 28
        if x > 0 and (not x in sol):
            sol.append(x)
sol.sort()
ret = 0
for i in xrange(30):
    ret += sol[i]
print ret
