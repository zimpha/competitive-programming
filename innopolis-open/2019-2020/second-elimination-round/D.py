from math import sqrt, gcd

def isqrt(n):
    x = int(sqrt(n))
    while True:
        y = (x + n // x) // 2
        if y >= x: break
        x = y
    return x

def factor(n, u):
    a = isqrt(n)
    while True:
        a += 1
        b = isqrt(a * a - n)
        if a * a - b * b == n:
            if a + b == u or a - b == u:
                continue
            return a + b, a - b

b, k = map(int, input().split())
n = int(input(), 16)
a, b = factor(n, -1)
if k == 2:
    print(hex(a)[2:])
    print(hex(b)[2:])
else:
    c, d = factor(n, a)
    print(hex(gcd(a, c))[2:])
    print(hex(gcd(a, d))[2:])
    print(hex(gcd(b, c))[2:])
    print(hex(gcd(b, d))[2:])
