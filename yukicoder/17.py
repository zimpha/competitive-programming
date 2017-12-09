n = int(input())
s = [int(input()) for i in range(n)]
g = [[1 << 30] * n for i in range(n)]
m = int(input())
for i in range(m):
  a, b, c = list(map(int, input().split()))
  g[a][b] = c
  g[b][a] = c

for i in range(n):
  g[i][i] = 0

for k in range(n):
  for i in range(n):
    for j in range(n):
      g[i][j] = min(g[i][j], g[i][k] + g[k][j])

ret = 1 << 30
for i in range(1, n - 1):
  for j in range(1, n - 1):
    if i == j:
      continue
    ret = min(ret, s[i] + s[j] + g[0][i] + g[i][j] + g[j][n - 1])
print(ret)
