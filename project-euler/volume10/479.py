# (a_k+b_k)(b_k+c_k)(c_k+a_k) = 1 - k^2
M = 10 ** 9 + 7

def inv(n):
    return pow(n, M - 2, M)

def S(n):
    r = 0
    for k in xrange(1, n + 1):
        a = 1 - k * k
        if a == 0:
            continue
        r += a * (pow(a, n, M) - 1) * inv(a - 1)
        r %= M
    r = (r + M) % M
    return r

print S(4)
print S(10 ** 6)
