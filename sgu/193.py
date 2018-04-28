n = int(input())
if n & 1 == 1:
  print(n >> 1)
elif n & 3 == 0:
  print((n >> 1) - 1)
else:
  print((n >> 1) - 2)
