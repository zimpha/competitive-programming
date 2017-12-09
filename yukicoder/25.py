from fractions import gcd

def valid(n):
  while n % 2 == 0:
    n //= 2
  while n % 5 == 0:
    n //= 5
  return n == 1

n = int(input())
m = int(input())
g = gcd(n, m)
n //= g
m //= g
if valid(m):
  q, r = divmod(n, m)
  if q > 0:
    ret = str(q).rstrip('0')[-1]
  else:
    ret = -1
  while r != 0:
    q, r = divmod(r * 10, m)
    if q != 0:
      ret = q
  print(ret)
else:
  print(-1)
