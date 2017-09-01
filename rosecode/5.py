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
    if x >= 1000: break
    for y in p:
        if y == x: break
        a = int(str(x) + str(y))
        b = int(str(y) + str(x))
        if mark[a] and mark[b]:
            ret += 1
print ret
