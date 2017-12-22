def a_very_easy_sum(n, mod):
  def f(n):
    return n * (n + 1) / 2
  u = int(n ** (1. / 3))
  mu = [0] * (u + 1)
  for i in xrange(1, u + 1):
    mu[i] += i == 1
    for j in xrange(i + i, u + 1, i):
      mu[j] -= mu[i]
  ret = 0
  for i in xrange(1, u + 1):
    ret += mu[i] * i ** 3 * f(n / i ** 3)
  return ret % mod

print a_very_easy_sum(10, 10 ** 9 + 7)
print a_very_easy_sum(10 ** 4, 10 ** 9 + 7)
print a_very_easy_sum(123456789123456789, 10 ** 9 + 7)
