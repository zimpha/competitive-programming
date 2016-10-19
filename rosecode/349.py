def exgcd(a, b):
    if b == 0:
        return (a, 1, 0)
    else:
        g, y, x = exgcd(b, a % b)
        y -= x * (a / b)
        return (g, x, y)

def inv(a, m):
    if m == 1:
        return 1
    d, x, y = exgcd(a, m)
    return (x % m + m) % m

def is_periodic(s):
    n = len(s)
    for t in xrange(1, n):
        if n % t == 0:
            flag = True
            for i in xrange(t, n):
                if s[i] != s[i - t]:
                    flag = False
            if flag:
                return True
    return False

def solve(m, factor):
    N = 10 ** m - 1
    n = len(factor)
    cnt, sum = 0, 0
    for msk in xrange(1, 2 ** n):
        d = 1
        for i in xrange(n):
            if msk >> i & 1 == 1:
                d *= factor[i]
        X = str(d * inv(d, N / d))
        if len(X) == m and is_periodic(X):
            cnt += 1
            sum += int(X)
    return cnt, sum

factor = [9, 11, 41, 271, 9091]
print solve(10, factor)
factor = [9, 11, 101, 103, 4013, 2071723, 28559389, 1491383821, 5363222357, 21993833369, 2324557465671829]
print solve(68, factor)
