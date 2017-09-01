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
dis, last = -1, -1
for i in xrange(1, len(p)):
    if p[i] - p[i - 1] == 2:
        if last != -1:
            dis = max(dis, p[i] - last)
        last = p[i]
print dis
