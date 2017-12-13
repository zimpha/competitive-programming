n = int(input())
v = list(map(int, input().split()))
f = [0] * n
g = [0] * n
f[0] = v[0]
for i in range(1, n):
  f[i] = g[i - 1] + v[i]
  g[i] = max(f[i - 1], g[i - 1])
print(max(f[-1], g[-1]))
