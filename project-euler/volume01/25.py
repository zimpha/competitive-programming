def sol(n):
  f1 = 1
  f2 = 1
  i = 3
  while True:
    t = f1 + f2
    f1, f2 = f2, t
    if len(str(t)) == n:
      return i
    i = i + 1
  return -1

print sol(1000)
