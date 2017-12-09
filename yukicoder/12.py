def init_primes(n):
  mark = [0] * (n + 1)
  ps = []
  for i in range(2, n + 1):
    if not mark[i]: ps.append(i)
    for p in ps:
      if p * i > n: break
      mark[p * i] = 1
      if i % p == 0: break
  return ps

input()
ds = set(input().split())
s = set()
ret, last = -1, 1
n = 5000000

for p in init_primes(n):
  t = set(str(p))
  if len(t - ds) > 0:
    if len(ds) == len(s):
      ret = max(ret, p - 1 - last)
    s = set()
    last = p + 1
  else:
    s |= t
if len(ds) == len(s):
  ret = max(ret, n - last)
print(ret)
