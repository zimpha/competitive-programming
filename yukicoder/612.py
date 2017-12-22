mod = 10 ** 9 + 7
T = int(input())
a, b, c, d, e = list(map(int, input().split()))
a = abs(a)
b = abs(b)
c = abs(c)
n, offset = 20000 + 2, 10000
f = [0] * n
f[offset] = 1
for i in range(T):
  g = [0] * n
  for j in range(n):
    f[j] %= mod
    if j >= a: g[j - a] += f[j]
    if j >= b: g[j - b] += f[j]
    if j >= c: g[j - c] += f[j]
    if j + a < n: g[j + a] += f[j]
    if j + b < n: g[j + b] += f[j]
    if j + c < n: g[j + c] += f[j]
  f = g
ret = 0
for i in range(d, e + 1):
  ret += g[i + offset]
print(ret % mod)
