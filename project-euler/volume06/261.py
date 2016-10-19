import pe

def calc(n):
  r, i = 1, 2
  while i * i <= n:
    if n % i == 0:
      c = 0
      while n % i == 0: n, c = n / i, c + 1
      r *= i ** ((c + 1) / 2)
    i += 1
  if n > 1:
    r *= n
  return r

pivots = set()
for m in xrange(1, 100000):
  sm = calc(m)
  sol = pe.quad_s(m / sm, (m + 1) * sm, m / sm * (m + 1), 10 ** 20)
  for x, y in sol:
    n, k = x - m - 1, y + m / sm
    if n % 2 == 0 and k % 2 == 0:
      n, k = n / 2, sm * k / 2
      if k <= n and k <= 10 ** 10:
        pivots.add(k)
print sum(pivots)

