from math import gcd

def exgcd(a, b):
    if b == 0:
        return 1, 0
    else:
        x, y = exgcd(b, a % b)
        x -= a // b * y
        return y, x

x, y, m, n, L = map(int, input().split())
a = n - m
b = L
c = x - y
r = gcd(a, b)
if c % r != 0:
    print("Impossible")
else:
    a //= r
    b //= r
    c //= r
    x, y = exgcd(a, b)
    t = c * x // b
    x = x * c - t * b
    if x < 0:
        x += b
    print(x)
