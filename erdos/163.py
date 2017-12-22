from fractions import *
import sys

def bored_with_shinigami():
    mod = 10 ** 9 + 7
    sys.setrecursionlimit(10 ** 6)
    def fib(n):
        if n == 0:
            return 0, 1
        if n & 1:
            y, x = fib(n - 1)
            return x, (x + y) % mod
        else:
            x, y = fib(n >> 1)
            return (x * y + x * (y - x)) % mod, (x * x + y * y) % mod
    n = 101 ** 2185 - 17 ** 2185
    m = 101 ** 4807 - 17 ** 4807
    g = gcd(n, m)
    return fib(g)[0]

print bored_with_shinigami()
