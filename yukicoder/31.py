def solve():
  n, v = list(map(int, input().split()))
  c = list(map(int, input().split()))
  s = [x for x in c]
  for i in range(1, n):
    s[i] += s[i - 1]
  v -= n
  if v <= 0:
    return s[-1]
  m = min(20000, v)
  dp = [0] * (m + 1)
  x = 0
  for i in range(n):
    if s[i] * (x + 1) < s[x] * (i + 1):
      x = i
  for i in range(0, m + 1):
    dp[i] = 2 ** 60
    if (v - i) % (x + 1) == 0:
      dp[i] = (v - i) // (x + 1) * s[x]
  for i in range(m, -1, -1):
    for j in range(n):
      if i + j + 1 > m: continue
      dp[i] = min(dp[i], dp[i + j + 1] + s[j])
  return dp[0] + s[-1]

print(solve())
