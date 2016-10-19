def run(n):
    fib = [0, 1]
    for i in xrange(2, n * 2 + 10):
        fib.append(fib[i - 1] + fib[i - 2])
    return fib[2 * n] * fib[2 * n + 1]

print run(1)
print run(10)
print run(15)
