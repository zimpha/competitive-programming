s = 0
for i in xrange(1, 1001):
  s += pow(i, i, 10000000000L)
print (s % 10000000000L)
