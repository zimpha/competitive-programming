n = 1000001
dv = {}
for i in xrange(n):
    dv[i] = set()
for i in xrange(1, n):
    for j in xrange(i + i, n, i):
        dv[j].add(i)

mx, ret = 0, 0
for i in xrange(1, n):
    vis = {}
    x = i
    cnt = 1
    vis[x] = 0
    while True:
        y = sum(dv[x])
        if y >= n:
            break
        if y in vis:
            if y == i:
                tmp = cnt - vis[y]
                if tmp > mx:
                    mx = tmp
                    ret = i
            break
        vis[y] = cnt
        cnt += 1
        x = y
print ret, mx
