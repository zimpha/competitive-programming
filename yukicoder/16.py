mod = 10 ** 6 + 3
x, n = list(map(int, input().split()))
a = list(map(int, input().split()))
r = 0
for e in a:
  r += pow(x, e, mod)
print(r % mod)
