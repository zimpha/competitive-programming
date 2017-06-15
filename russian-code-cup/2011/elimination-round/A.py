n = 1000
f = [0] * n
for i in xrange(0, n - 1):
  f[i + 1] = (f[i] + 1) * 0.5 + (f[i] + 2 + i) * 0.5
for it in xrange(int(raw_input())):
  print '%.10f' % f[int(raw_input()) - 1]
