def f(n):
    if n == 1 or n == 89:
        return n
    s = 0
    while n > 0:
        s += (n % 10) * (n % 10)
        n /= 10
    return f(s)

ret = 0
for i in xrange(1, 10000001):
    x = f(i)
    if x == 89:
        ret += 1
print ret
