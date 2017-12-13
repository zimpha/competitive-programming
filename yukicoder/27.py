def count(a, b):
  n = max(b)
  dp = [1e9] * (n + 1)
  dp[0] = 0
  for x in a:
    for i in range(x, n + 1):
      dp[i] = min(dp[i], dp[i - x] + 1)
  return sum([dp[x] for x in b])

v = list(map(int, input().split()))
ret = 1e9
for x in range(1, 31):
  for y in range(1, 31):
    for z in range(1, 31):
      ret = min(ret, count([x, y, z], v))
print(ret)
