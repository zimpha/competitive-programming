n = int(input())
m = int(input())
a = list(map(int, input().split()))
inf = 1 << 60

f = [inf] * (m + 1)
f[0] = 0
for i, x in enumerate(a):
    g = [inf] * (m + 1)
    for j in range(m + 1):
        if f[j] == inf: continue
        if j + x <= m:
            g[j + x] = min(g[j + x], f[j])
        if j * x <= m:
            g[j * x] = min(g[j * x], f[j] | (1 << (n - i)))
    f = g
mask = f[m]
res = []
for i in range(n - 1, 0, -1):
    if mask >> i & 1:
        res.append('*')
    else:
        res.append('+')
print(''.join(res))
