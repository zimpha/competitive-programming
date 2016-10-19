f = {}
f[0] = 1
for i in xrange(1, 101):
  f[i] = f[i - 1] * i

ret = 0
for i in xrange(1, 101):
  for j in xrange(0, i + 1):
    c = f[i] / f[j] / f[i - j]
    if c > 1000000L:
      ret += 1

print ret
