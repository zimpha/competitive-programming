# G(x) = x^k/k * e^(-x^k/k) / (1 - x)
def S(n, k):
  mod = 10 ** 9 + 7
  ret = 0
  fac, pk, s = 1, 1, 1
  for i in range(n):
    if i * k + k > n:
      break
    ret += pow(fac * pk, mod - 2, mod) * s % mod
    s = mod - s
    fac = fac * (i + 1) % mod
    pk = pk * k % mod
  ret %= mod
  for i in range(1, n + 1):
    ret = ret * i % mod
  return ret * pow(k, mod - 2, mod) % mod

for n in range(1, 11):
  for k in range(1, n + 1):
    print S(n, k),
  print ''
print S(10 ** 7, 50)
