mod = 10 ** 9 + 9

def inverse(x):
  if x == 1: return 1
  else: return (mod - mod // x) * inverse(mod % x) % mod

n = 10 ** 6
coins = [5, 10, 50, 100, 500]
dp = [1] * n
for c in coins:
  for i in range(c, n):
    dp[i] = (dp[i] + dp[i - c]) % mod
for _ in range(int(input())):
  m = int(input())
  x, r = divmod(m, 500)
  ret = 0
  for k in range(6):
    tmp = 1
    for i in range(6):
      if k == i: continue
      tmp = tmp * (x - i + mod) % mod
    for i in range(6):
      if k == i: continue
      tmp = tmp * inverse((k - i + mod) % mod) % mod
    ret = (ret + tmp * dp[k * 500 + r]) % mod
  print(ret)
