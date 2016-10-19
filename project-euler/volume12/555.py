# T = k - s, val = m + k - s * 2
def M(m, k, s, n):
  if n > m:
    return n - s
  else:
    return M(m, k, s, M(m, k, s, n + k))

def SF(m, k, s):
  val = m + k - s * 2
  x = (2 * s - k) / (k - s)
  r = m - x * (k - s)
  assert r >= 0
  l = max(m - (x + 1) * (k - s) + 1, 0)
  len = r - l + 1
  return (val + val - len + 1) * len / 2
  
def S(p, m):
  ret = 0
  for t in xrange(1, p):
    # k = 2s, x = 0
    k, s = 2 * t, t
    if 1 <= s and s < k and k <= p:
      ret += SF(m, k, s)
    for v in xrange(t, p, t):
      # t = k - s, v = 2s - k
      k, s = 2 * t + v, t + v
      if 1 <= s and s < k and k <= p:
        ret += SF(m, k, s)
  return ret

print S(10, 10)
print S(1000, 1000)
print S(10 ** 6, 10 ** 6)
