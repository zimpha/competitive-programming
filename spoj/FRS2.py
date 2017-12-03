mod = 10 ** 9 + 7
p1 = 2000000016
p2 = 329616

def fib(n, mod):
    if n == 0: return 0, 1
    if n % 2:
        y, x = fib(n - 1, mod)
        return x, (x + y) % mod
    else:
        a, b = fib(n >> 1, mod)
        return (a * b + a * (b - a + mod)) % mod, (a * a + b * b) % mod;


for _ in xrange(input()):
    n = input() % p2
    m = fib(n, p1)[0]
    print fib(m, mod)[0]
