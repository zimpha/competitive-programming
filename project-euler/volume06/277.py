def gcd(x, y):
    return x if y == 0 else gcd(y, x % y)

def exgcd(a, b):
  if b == 0:
    return (1, 0)
  q, r = divmod(a, b)
  s, t = exgcd(b, r)
  return t, s - q * t

def run(s, upp):
  a, b, c = 1, 0, 1
  for x in s:
    if x == 'D':
      c *= 3
    elif x == 'U':
      a *= 4
      b = b * 4 + c * 2
      c *= 3
    else:
      a *= 2
      b = b * 2 - c
      c *= 3
  b, c = c, b
  # ax + c = by
  g = gcd(a, b)
  if c % g != 0:
    return -1
  x, y = exgcd(a, -b)
  x = x * (c / g) % (b / g)
  y = (a * x + c) / b
  if x > upp:
    x -= (x - upp) / b * b;
  while x <= upp:
    x += b
  return x

print run("DdDddUUdDD", 10 ** 6)
print run("UDDDUdddDDUDDddDdDddDDUDDdUUDd", 10 ** 15)
