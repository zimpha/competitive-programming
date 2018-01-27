from math import *

n = 1000
f = [0] * (n + 1)
for i in range(1, n + 1):
  f[i] = f[i - 1] + log(i)
mx, p = -1e9, 1
for i in range(2, n + 1):
  r = log(i - 1) - i * log(1000) + f[1000] - f[1000 - i + 1]
  if r > mx:
    mx = r
    p = i
print mx, p
r = 1
factors = [3, 11]
for p in factors:
  r *= p + pi
print r
