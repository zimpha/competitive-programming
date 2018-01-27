def f(x):
  return x ** 4 + 1

r = 0
for i in range(2, 222 + 1):
  r += f(i)
print r
