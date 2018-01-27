from fractions import *

n = 251277
a = Fraction(1)
b = Fraction(0)
for i in xrange(n):
  p = Fraction(1, 2 * i + 5)
  c = a * (1 - p) + b * p
  d = a * p + b * (1 - p)
  a, b = c, d
print a
