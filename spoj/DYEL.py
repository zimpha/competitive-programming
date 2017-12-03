from fractions import *
import copy

for _ in xrange(int(raw_input())):
    s = map(int, raw_input().split())[1:]
    if max(s) == 0:
        print 1
        continue
    C = [Fraction(1)]
    B = [Fraction(1)]
    L, m = 0, 1
    b = Fraction(1)
    for n in xrange(len(s)):
        d = Fraction(s[n])
        for i in xrange(1, L + 1):
            d += C[i] * s[n - i]
        if d == 0: m += 1
        elif L * 2 <= n:
            T = copy.deepcopy(C)
            l = max(len(C), m + len(B))
            C.extend([Fraction(0)] * (l - len(C)))
            for i in xrange(0, len(B)):
                C[i + m] -= d / b * B[i]
            L = n + 1 - L
            B = T
            b = d
            m = 1
        else:
            l = max(len(C), m + len(B))
            C.extend([Fraction(0)] * (l - len(C)))
            for i in xrange(0, len(B)):
                C[i + m] -= d / b * B[i]
            m += 1
    res = [str(-int(x)) for x in C]
    print ' '.join(res[1:])
