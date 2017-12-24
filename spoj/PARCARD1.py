n, m = 100000000, 10001
f = [0] * (n + 1)
f[0] = 1
for i in range(1, m):
  g = [x for x in f]
  for j in range(n + 1):
    if j >= i:
      g[j] += g[j - i]
  f = g
g = [x for x in f]
for i in range(1, m):
  h = [0] * (n + 1)
  for j in range(n + 1):
    if j >= m:
      h[j] += f[j - m]
    if j >= i:
      h[j] += h[j - i]
    g[j] += h[j]
  f = h
print(g[-1])
