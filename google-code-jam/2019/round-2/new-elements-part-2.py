from fractions import *

def solve(L, R):
    L += Fraction(1, 10 ** 20)
    l = (0, 1)
    r = (1, 0);
    while True:
      m = (l[0] + r[0], l[1] + r[1])
      if m[0] < L * m[1]:
        kl = 1
        kr = 1
        while l[0] + kr * r[0] <= L * (l[1] + kr * r[1]):
          kr *= 2
        while kl < kr:
          km = (kl + kr) / 2;
          if l[0] + km * r[0] < L * (l[1] + km * r[1]):
            kl = km + 1
          else:
            kr = km;
        l = (l[0] + (kl - 1) * r[0], l[1] + (kl - 1) * r[1])
      elif m[0] >= R * m[1]:
        kl = 1
        kr = 1
        while r[0] + kr * l[0] >= R * (r[1] + kr * l[1]):
          kr *= 2
        while kl < kr:
          km = (kl + kr) / 2
          if r[0] + km * l[0] >= R * (r[1] + km * l[1]):
            kl = km + 1
          else:
            kr = km
        r = (r[0] + (kl - 1) * l[0], r[1] + (kl - 1) * l[1])
      else:
        return m

def sol(n, C, J):
  l = Fraction(1, 10 ** 20)
  r = Fraction(10 ** 20, 1)
  for i in range(n):
    for j in range(i + 1, n):
      if C[i] == C[j] and J[i] > J[j]:
        return "IMPOSSIBLE"
      if C[i] == C[j] and J[i] < J[j]:
        continue
      if J[i] == J[j] and C[i] > C[j]:
        return "IMPOSSIBLE"
      if J[i] == J[j] and C[i] < C[j]:
        continue
      if C[i] <= C[j] and J[i] <= J[j]:
        continue
      t = Fraction(J[j] - J[i], C[i] - C[j])
      if C[i] > C[j]:
        r = min(r, t)
      else:
        l = max(l, t)
  if l >= r:
    return "IMPOSSIBLE"
  l, r = 1 / r, 1 / l
  y, x = solve(l, r)
  return '{} {}'.format(x, y)
 
T = int(raw_input())
for cas in range(1, T + 1):
  n = int(raw_input())
  C = []
  J = []
  for i in range(n):
    c, j = map(int, raw_input().split())
    C.append(c)
    J.append(j)
  print 'Case #{}: {}'.format(cas, sol(n, C, J))
