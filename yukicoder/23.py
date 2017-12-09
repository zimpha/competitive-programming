h, a, d = list(map(int, input().split()))

mem = [-1] * (h + 1)
def dp(c):
  if c <= 0: return 0
  if mem[c] >= 0: return mem[c]
  mem[c] = min(1 + dp(c - a), 1.5 + dp(c - d))
  return mem[c]
print(dp(h))
