base = 2 ** 16384
for _ in range(int(input())):
  a, b, c, d = list(map(int, input().split()))
  n = (a ** b) ^ (c ** d)
  r = 0
  while n:
    r += n % base
    n //= base
  print(r)
