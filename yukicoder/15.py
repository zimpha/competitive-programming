def convert(mask, n):
  r = []
  for i in range(n):
    if mask >> i & 1:
      r.append(i + 1)
  return r

n, s = list(map(int, input().split()))
p = [int(input()) for i in range(n)]

x, y = n // 2, n - n // 2
cache = dict()
for mask in range(1 << x):
  r = 0
  for i in range(x):
    if mask >> i & 1:
      r += p[i]
  if r in cache:
    cache[r].append(mask)
  else:
    cache[r] = [mask]

ret = []
for mask in range(1 << y):
  r = s
  for i in range(y):
    if mask >> i & 1:
      r -= p[i + x]
  if r in cache:
    for e in cache[r]:
      ret.append(e | (mask << x))
ret = [convert(mask, n) for mask in ret]
ret.sort()
for e in ret:
  print(*e)
