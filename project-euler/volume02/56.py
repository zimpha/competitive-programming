def gao(n):
  s = str(n)
  r = 0
  for i in xrange(len(s)):
    r += ord(s[i]) - ord('0')
  return r

r = 0
for a in xrange(1, 100):
  for b in xrange(1, 100):
    t = gao(a ** b)
    if t > r:
      r = t
print r
