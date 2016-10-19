def is_squarefree(n, r):
    for i in xrange(2, r + 1):
        if n % i == 0:
            n /= i
            if n % i == 0:
                return False
    return True

def fac(n):
    r = 1
    for i in xrange(1, n):
        r *= i + 1
    return r

def run(n):
    s = set()
    for i in xrange(0, n):
        for j in xrange(0, i + 1):
            b = fac(i) / fac(j) / fac(i - j)
            if is_squarefree(b, n):
                s.add(b)
    return sum(s)

print run(8)
print run(51)
