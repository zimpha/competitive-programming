mod = 10 ** 9 + 7

def fib(n):
  if n == 1:
    return 1, 1
  if n & 1:
    y, x = fib(n - 1)
    return x, (x + y) % mod
  else:
    x, y = fib(n >> 1)
    return (x * y + x * (y - x + mod)) % mod, (x * x + y * y) % mod

print(fib(10 ** 18 + 3)[0] - 1)
