n = int(input())
a = list(map(int, input().split()))
m = int(input())
b = list(map(int, input().split()))
b.sort(reverse=True)

weight = [0] * (1 << n)
for mask in range(1, 1 << n):
  for i in range(n):
    weight[mask] += (mask >> i & 1) * a[i]

f = [False] * (1 << n)
f[0] = True
ret = -1
for i in range(m):
  g = [x for x in f]
  for mask in range(1 << n):
    if not f[mask]: continue
    rest = mask ^ ((1 << n) - 1)
    sub = rest
    while sub:
      if weight[sub] <= b[i]:
        g[mask | sub] = True
      sub = (sub - 1) & rest
  f = g
  if f[-1]:
    ret = i + 1
    break
print(ret)
