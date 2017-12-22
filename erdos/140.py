from fractions import *

def P(n):
  r = 1
  for i in xrange(1, n + 1):
    if gcd(i, n) == 1:
      r = r * i % n
  return r

def brute(n):
  r = 0
  for i in xrange(n):
    r += P(i + 1)
  return r

def F(n):
  if n <= 1: return 0
  def f(n):
    return n * (n + 1) // 2 - 1
  v = int(n ** 0.5)
  scnt = [i - 1 for i in range(v + 1)]
  ssum = [f(i) for i in range(v + 1)]
  lcnt = [n // i - 1 if i else 0 for i in range(v + 1)]
  lsum = [f(n // i) if i else 0 for i in range(v + 1)]

  for p in range(2, v + 1):
    if scnt[p] == scnt[p - 1]:
      continue
    p_cnt = scnt[p - 1]
    p_sum = ssum[p - 1]
    q = p * p
    end = min(v, n // q)
    for i in range(1, end + 1):
      d = i * p
      if d <= v:
        lcnt[i] -= lcnt[d] - p_cnt
        lsum[i] -= (lsum[d] - p_sum) * p
      else:
        t = n // d
        lcnt[i] -= scnt[t] - p_cnt
        lsum[i] -= (ssum[t] - p_sum) * p
    for i in range(v, q - 1, -1):
      t = i // p
      scnt[i] -= scnt[t] - p_cnt
      ssum[i] -= (ssum[t] - p_sum) * p
  ret = lsum[1] - lcnt[1]
  count = n - 1 - lcnt[1]
  ret += 2 * lsum[2] - lcnt[2]
  count -= lcnt[2]
  for p in xrange(3, v + 1):
    if scnt[p] == scnt[p - 1]:
      continue
    for a in xrange(2, 100):
      if p ** a > n:
        break
      ret += p ** a - 1
      count -= 1
      if p ** a * 2 <= n:
        ret += p ** a * 2 - 1
        count -= 1
  return ret + count

def bored_with_gcd():
  mod = 10 ** 9 + 7
  total = 0
  for i in xrange(1, 13):
    total += F(10 ** i)
  return total % mod

print bored_with_gcd()
