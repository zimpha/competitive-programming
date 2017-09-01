n = 1000000 * 5
mark = [True] * n
p = []
for i in xrange(2, n):
    if mark[i]:
        p.append(i)
    for x in p:
        if x * i >= n:
            break
        mark[i * x] = False
        if i % x == 0:
            break
print p[10000 - 1]
print p[78200 - 1]
