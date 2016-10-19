from math import *

def pell(D):
  sqrtD = int(sqrt(D))
  if sqrtD * sqrtD == D:
    return -1
  c = sqrtD
  q = D - c * c
  a = (c + sqrtD) / q
  step = 0
  X = {}
  Y = {}
  X[0], X[1] = 1, sqrtD
  Y[0], Y[1] = 0, 1
  while True:
    X[step] = a * X[step ^ 1] + X[step]
    Y[step] = a * Y[step ^ 1] + Y[step]
    c = a * q - c
    q = (D - c * c) / q
    a = (c + sqrtD) / q
    step ^= 1
    if c == sqrtD and q == 1 and step == 1:
      return X[0], Y[0]

# a, a, b
ret = 0
# case 1: b = a + 1, x = (3a - 1) / 2, y = h
x1, y1 = pell(3)
x, y = x1, y1
while True:
    a = (2 * x + 1) / 3
    if a * 3 + 1 > 1e9:
        break
    if (2 * x + 1) % 3 == 0:
        a = (2 * x + 1) / 3
        ret += a * 3 + 1
    x, y = x1 * x + 3 * y1 * y, x1 * y + y1 * x
# case 2: b = a - 1, x = (3a + 1) / 2, y = h
x, y = x1, y1
while True:
    a = (2 * x - 1) / 3
    if a * 3 - 1 > 1e9:
        break
    if (2 * x - 1) % 3 == 0:
        a = (2 * x - 1) / 3
        if a > 1:
            ret += a * 3 - 1
    x, y = x1 * x + 3 * y1 * y, x1 * y + y1 * x
print ret
