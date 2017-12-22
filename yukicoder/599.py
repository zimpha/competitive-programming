seed, mod = 65537, 10 ** 9 + 7

s = input()
n = len(s)

hs = [0] * (n + 1)
pw = [1] * (n + 1)
for i in range(1, n + 1):
    pw[i] = pw[i - 1] * seed % mod
for i in range(n, 0, -1):
    hs[i - 1] = (hs[i] * seed + ord(s[i - 1])) % mod

def hash_value(l, r):
    return (hs[l] - hs[r] * pw[r - l] % mod + mod) % mod

dp = [1] * (n // 2 + 1)
for i in range(n // 2):
    dp[i + 1] = 0
    for j in range(i + 1):
        if hash_value(j, i + 1) == hash_value(n - i - 1, n - j):
            dp[i + 1] += dp[j]
    dp[i + 1] %= mod
print(sum(dp) % mod)
