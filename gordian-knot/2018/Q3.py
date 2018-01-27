from fractions import gcd
N = 10 ** 6
p = [0] * N
for i in range(2, N):
  if p[i]: continue
  for j in range(i + i, N, i):
    p[j] = 1
for n in range(2, N):
  if not p[n]: continue
  flag = True
  for a in range(2, n + 1):
    if gcd(a, n) != 1: continue
    if pow(a, n, n) != a:
      flag = False
      break
  if flag:
    print n
    break
