def ok(n):
  n += int(str(n)[::-1])
  for i in xrange(50):
    s = str(n)
    s = s[::-1]
    t = int(s)
    if t == n:
      return 0
    n += t
  return 1

print ok(47)
print ok(349)
print ok(4994)
ret = 0
for n in xrange(1, 10001):
  ret += ok(n)
print ret
