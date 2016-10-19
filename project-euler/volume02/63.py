from math import *

ret = 0
i = 0
for n in xrange(1, 1000):
  i = ceil(pow(10, (n - 1.0) / n));
  ret += 10 - i
  if i >= 10:
    break
  print n
print ret
