from fractions import gcd

mod = 10 ** 9 + 7
n, m, t = map(int, input().split())
a = gcd(n, t)
b = gcd(m, t)
n //= a
m //= b
ret = pow(2, n, mod) + pow(2, m, mod) + pow(2, gcd(n, m), mod) - 3
print(pow(ret, a * b, mod))
