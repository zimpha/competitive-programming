def fac(n):
  r = 1
  for i in xrange(n):
    r *= i + 1
  return r

def divisor(n):
  d = []
  for i in xrange(1, n + 1):
    if n % i == 0:
      d.append(i)
  return d

def phi(n):
  r, i = n, 2
  while i * i <= n:
    if n % i == 0:
      r = r / i * (i - 1)
      while n % i == 0: n /= i
    i += 1
  if n > 1:
    r = r / n * (n - 1)
  return r

def f(m, n):
  if n == 1: return fac(m - 1)
  d = divisor(n)
  r = 0
  for x in d:
    r += fac(m * x) / fac(x) ** m * phi(n / x)
  r /= m * n
  return r

def run(upp):
  r = 0
  for m in xrange(2, 20):
    for n in xrange(1, 100):
      now = f(m, n)
      if f(m, n) > upp:
        break
      r += now
  return r
print run(10 ** 15)
