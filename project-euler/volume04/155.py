from fractions import *

D = []
D.append(set({Fraction(1,1)}))
for n in xrange(2, 19):
    s = set()
    for a in xrange(1, n):
        b = n - a
        if b > a:
            continue
        for x in D[a-1]:
            for y in D[b-1]:
                s.add(x + y)
                s.add(x * y / (x + y))
    D.append(s)
    print len(s)
for i in xrange(2, 19):
    for x in D[i - 1]:
        D[0].add(x)
print len(D[0])
