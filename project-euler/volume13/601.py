from fractions import *

def lcm(n, m):
    return n * m / gcd(n, m);

def P(s, N):
    N -= 1
    a = 1
    for i in xrange(2, s + 1):
        a = lcm(a, i)
    b = lcm(a, s + 1);
    return N / a - N / b

ret = 0
for i in xrange(1, 32):
    ret += P(i, 4 ** i)
print ret - 1
