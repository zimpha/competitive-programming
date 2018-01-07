from fractions import gcd
n = int(input())
tests = []
for i in range(n):
  a = int(input())
  b = int(input())
  tests.append((a, i))
  tests.append((b, i))
tests.sort()
ia = [0] * n
ib = [0] * n
a, b, m, i = 0, 1, 1, 0
for e in tests:
  while b < e[0]:
    a, b = b, a + b
    m += 1
  if not ia[e[1]]:
    ia[e[1]] = m
  else:
    ib[e[1]] = m
ic = [gcd(x, y) for x, y in zip(ia, ib)]
tests = [(x, i) for i, x in enumerate(ic)]
tests.sort()
a, b, m = 0, 1, 1
ret = [0] * n
for e in tests:
  while m < e[0]:
    a, b = b, a + b
    m += 1
  ret[e[1]] = b
for x in ret:
  print(x)
