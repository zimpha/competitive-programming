def g(m, n, p):
  a, b, c = m, n, m % n
  while c > 0:
    if 5 * c * c < p:
      if p == b * b + 3 * b * c + c * c:
        return b, c
      t = b - c
      if p == t * t + 3 * t * c + c * c:
        return t, c
    a, b, c = b, c, a % b
  return -1, -1

def rep(p):
  v = mod(5, p).sqrt()
  v = (v - 1) * (p + 1) / 2 % p
  if v * 2 > p:
    v = p - v - 1
  return g(p, v, p)

def run(n, m):
  P = Primes()
  sx, sy = 0, 0
  while m > 0:
    n = P.next(n)
    if n % 5 == 1:
      m -= 1
      x, y = rep(n)
      if x > y:
        x, y = y, x
      sx += x
      sy += y
  print sx, sy

run(10 ** 50, 100)
