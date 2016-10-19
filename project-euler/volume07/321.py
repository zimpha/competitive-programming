# M(n) = n * (n + 2)
def run(n):
  # x = 3x + y + 2
  # y = 8x + 3y + 8
  # (x, y) = (0, 1), (1, 5)
  ok = []
  x, y = 0, 1;
  for i in xrange(n):
    x, y = 3 * x + y + 2, 8 * x + 3 * y + 8;
    ok.append(x)
  x, y = 1, 5;
  for i in xrange(n):
    ok.append(x)
    x, y = 3 * x + y + 2, 8 * x + 3 * y + 8;
  ok.sort()
  ret = 0
  for i in xrange(n):
      ret += ok[i]
  return ret

print run(5)
print run(40)
