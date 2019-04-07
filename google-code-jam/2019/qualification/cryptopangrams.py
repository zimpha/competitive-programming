from fractions import *

T = int(raw_input())
for cas in range(1, T + 1):
  N, L = map(int, raw_input().split())
  c = map(int, raw_input().split())
  s = [0] * (L + 1)
  for i in range(1, L):
    if c[i] != c[i - 1]:
      g = gcd(c[i], c[i - 1])
      s[i] = g
      for j in range(i - 1, -1, -1):
        s[j] = c[j] / s[j + 1]
      for j in range(i, L):
        s[j + 1] = c[j] / s[j]
      break
  letters = sorted(list(set(s)))
  letters = {letters[i]: chr(ord('A') + i) for i in range(26)}
  s = [letters[x] for x in s]
  print 'Case #{}: {}'.format(cas, ''.join(s))
