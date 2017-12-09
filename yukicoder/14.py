from fractions import gcd

u = 10 ** 4
dv = [[] for i in range(u + 1)]
ds = [[] for i in range(u + 1)]
for i in range(1, u + 1):
  for j in range(i, u + 1, i):
    dv[j].append(i)

n = int(input())
a = list(map(int, input().split()))
for i, x in enumerate(a):
  for d in dv[x]:
    ds[d].append((x, i))
for e in ds:
  e.sort()
  e.reverse()

mark = [0] * n
ret, last = [a[0]], 0
for i in range(n - 1):
  mark[last] = 1
  r, x = 1 << 30, -1
  for d in dv[a[last]]:
    while len(ds[d]) and mark[ds[d][-1][1]]:
      ds[d].pop(-1)
    if not len(ds[d]):
      continue
    y = ds[d][-1][1]
    t = a[y] * a[last] / gcd(a[y], a[last])
    if t < r or (t == r and a[y] < a[x]):
      r, x = t, y
  last = x
  ret.append(a[x])
print(*ret)
