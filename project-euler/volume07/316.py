# g(n) = \sum 10 ^ k - |n|, where first k digist equals to last k digits
def g(n):
    s = str(n)
    ret = 1
    for k in xrange(1, len(s) + 1):
        a, b = s[:k], s[-k:]
        if a == b:
            ret += 10 ** k
    return ret - len(s)

def run(n, m):
    ret = 0
    for i in xrange(2, n):
        ret += g(m / i)
    return ret

print g(535)
print run(10 ** 3, 10 ** 6)
print run(10 ** 6, 10 ** 16)
