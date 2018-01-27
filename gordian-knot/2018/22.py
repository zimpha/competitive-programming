from math import cos, pi

n = [(2, 2), (3, 1), (19, 1), (10570841, 1), (104395301, 1)]
gn = 1
for p, k in n:
  r = 1
  for i in range(1, k + 1):
    r += p ** i
  gn *= r
print(gn)
