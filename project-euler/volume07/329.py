from fractions import *

def run(n, pat):
  is_prime = [True] * (n + 1)
  is_prime[0] = is_prime[1] = False
  for i in xrange(2, n + 1):
    if is_prime[i]:
      for j in xrange(i * 2, n + 1, i):
        is_prime[j] = False
  f = [Fraction(1, n)] * n
  for i in xrange(len(pat)):
    g = [Fraction(0)] * n
    for j in xrange(n):
      p = Fraction(1, 3)
      if (pat[i] == 'P') == is_prime[j + 1]:
        p = Fraction(2, 3)
      if j == 0:
        g[j + 1] += f[j] * p
      elif j == n - 1:
        g[j - 1] += f[j] * p
      else:
        g[j + 1] += f[j] * p * Fraction(1, 2)
        g[j - 1] += f[j] * p * Fraction(1, 2)
    f = g
  return sum(f)

print run(500, "PPPPNNPPPNPPNPN")
