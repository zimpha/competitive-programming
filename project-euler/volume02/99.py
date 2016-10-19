from math import *

ret = -1
mx = 0.0
for _ in xrange(0, 1000):
  a, b = input()
  if ret == -1 or b * log(a, 2) > mx:
    mx = b * log(a, 2)
    ret = _ + 1
print ret
