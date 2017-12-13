T = int(input())
n = int(input())
c = list(map(int, input().split()))
v = list(map(int, input().split()))
f = [0] * (T + 1)
for i in range(n):
  g = [x for x in f]
  total, need = 0, 0
  while v[i]:
    total += v[i]
    need += c[i]
    v[i] >>= 1
    for j in range(need, T + 1):
      g[j] = max(g[j], f[j - need] + total)
  f = g
print(max(f))
