# https://www.alpertron.com.ar/QUAD.HTM
# 5x^2 + 4x + 1 = y^2, 5x^2 - 4x + 1 = y^2
# x = -9x - 4y - 4
# y = -20x - 9y - 8
x, y = 0, 1
ret = 0
for i in xrange(12):
    x, y = -9 * x - 4 * y - 4, -20 * x - 9 * y - 8
    print x, y
    ret += abs(y)
print ret
