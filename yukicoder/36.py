def is_prime(n):
  if n <= 1: return False
  if n <= 3: return True
  if n % 2 == 0: return False
  u = [2, 3, 5, 7, 325, 9375, 28178, 450775, 9780504, 1795265022]
  e, c = n - 1, 0
  while e % 2 == 0:
    e >>= 1
    c += 1
  for p in u:
    if n <= p: return True
    a = pow(p, e, n)
    if a == 1:
      continue
    j = 1
    while a != n - 1:
      if j == c: return False
      a = a * a % n
      j += 1
  return True

def valid(n):
  if n == 1 or is_prime(n):
    return False
  i = 2
  while i ** 3 <= n:
    if n % i == 0:
      n //= i
      if n == 1 or is_prime(n):
        return False
      else:
        return True
    i += 1
  return False

print('YES' if valid(int(input())) else 'NO')
