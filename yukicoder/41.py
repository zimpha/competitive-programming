n, mod = 10 ** 5, 10 ** 9 + 9
dp = [0] * n
dp[0] = 1
for d in range(1, 10):
  for i in range(d, n):
    dp[i] += dp[i - d]
    dp[i] %= mod
for i in range(1, n):
  dp[i] = (dp[i] + dp[i - 1]) % mod

for _ in range(int(input())):
  m = int(input())
  print(dp[m // 111111])
