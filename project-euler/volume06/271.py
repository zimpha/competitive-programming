def run(pl):
  delta, mul = 1, 1
  for p in pl:
    cnt = 0
    for x in xrange(1, p):
      if pow(x, 3, p) == 1:
        cnt += 1
    if cnt == 1:
      delta *= p
    else:
      mul *= p
  print delta, mul
  x, r = 1, 0
  n = delta * mul
  while x < n:
    if x * x * x % mul == 1:
      r += x
    x += delta
  return r - 1

print run([7, 13])
print run([2,3,5,7,11,13,17,19,23,29,31,37,41,43])
