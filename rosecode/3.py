n = 1000000
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
ret = 0
for x in p:
    y = int(str(x)[::-1])
    if x == y:
        ret += x
print ret
