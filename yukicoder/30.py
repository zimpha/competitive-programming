n = int(input())
m = int(input())
edges = [[] for i in range(n)]
flag = [False] * n
for i in range(m):
  p, r, q = list(map(int, input().split()))
  edges[q - 1].append((p - 1, r))
  flag[q - 1] = True
dp = [[-1] * n for i in range(n)]

def dfs(i, j):
  res = 0
  if dp[i][j] >= 0: return dp[i][j]
  if i == j: return int(not flag[i])
  for k, c in edges[i]:
    res += dfs(k, j) * c
  dp[i][j] = res
  return res

for i in range(n - 1):
  print(dfs(n - 1, i))
