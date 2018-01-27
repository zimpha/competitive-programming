mod = 10 ** 9 + 7

def cnt(n):
  ret = 0
  if n % 2 == 1:
    ret = pow(3, n / 2, mod)
    n -= 1
  if n == 0:
    return ret
  if n == 2:
    return ret + 1 + 1
  m = n / 2
  ret += (pow(3, m, mod) - 1) * pow(2, mod - 2, mod) % mod
  if m % 2 == 0:
    m /= 2
    ret += m * 2 + 6 * (pow(9, m, mod) - 1) * pow(8, mod - 2, mod) % mod
  else:
    m /= 2
    ret += 1
    ret += m * 2 + 18 * (pow(9, m, mod) - 1) * pow(8, mod - 2, mod) % mod
  return ret % mod

print ((cnt(99999990000002) - cnt(123455)) % mod + mod) % mod
