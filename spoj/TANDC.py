mod = 10 ** 9 + 7
for i in range(int(input())):
  m, r = map(int, input().split())
  print(((pow(m, r, mod * (m - 1)) - 1 + mod * (m - 1)) % (mod * (m - 1)) // (m - 1) + mod - r) % mod)
