from math import gcd

a, b = map(int, input().split())
p = 10 ** 9 + 7
sign = 1
if a < 0:
    a = -a
    sign = -sign
if b < 0:
    b = -b
    sign = -sign
if a or b:
    g = gcd(a, b)
    a //= g
    b //= g
if b == 0 or (a != 0 and b % p == 0):
    print('No Solution!')
else:
    ans = a * pow(b, p - 2, p) % p * sign
    print(ans)
