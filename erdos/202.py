def sum_gp(n, a, q, mod):
  a %= mod
  q %= mod
  mem = {a : 0}
  s = [a]
  extra, perido = 0, 0
  for i in range(1, n + 1):
    a = a * q % mod
    if a in mem:
      extra = mem[a]
      period = i - mem[a]
      break
    s.append(a)
  if n <= len(s) - 1:
    return sum(s[:n+1])
  ret = sum(s[:extra])
  s = s[extra:]
  n -= extra
  ret += sum(s) * (n // period) + sum(s[:n % period + 1])
  return ret

def S(n, mod):
  ret = 0
  for r in range(1, 6):
    ret += sum_gp((n - r) // 6, 5 ** r, 5 ** 6, 10 ** r) % mod
  return ret % mod

print(S(10 ** 18, 10 ** 9 + 7))
