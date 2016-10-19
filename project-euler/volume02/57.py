a, b = 1, 1
ret = 0

for i in xrange(1000):
  a, b = a + 2 * b, a + b
  if len(str(a)) > len(str(b)):
    ret = ret + 1
print ret
