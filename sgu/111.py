from math import sqrt

def isqrt(s):
  d = len(s)
  n = int(s)
  if d % 2 == 0:
    x = 7 * 10 ** ((d - 2) // 2)
  else:
    x = 2 * 10 ** ((d - 1) // 2)
  x = (x + (n + x - 1) // x) >> 1
  while True:
    y = (x + (n + x - 1) // x) >> 1
    if y == x:
      break
    x = y
  if x * x > n:
    x -= 1
  return x

print(isqrt(input()))
