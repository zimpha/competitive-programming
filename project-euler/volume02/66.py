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
      return X[0]

mn = -1
ret = -1;
for D in xrange(1, 1001):
  x = pell(D)
  if x > mn:
    mn = x
    ret = D
print mn, ret
