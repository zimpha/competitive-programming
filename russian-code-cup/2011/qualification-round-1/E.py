# given i,j and k, find (a, b) where x=a/b < 0, y=ka/b < 0, y can be abtained by swap i-th and j-th position of the decimal expansion of x 
from fractions import gcd

i, j, k = map(int, raw_input().split())

def check(p, q, i, j, m):
    r = p * m
    a = [0] * (j + 1)
    b = [0] * (j + 1)
    for k in xrange(j + 1):
        p, r = p * 10, r * 10
        a[k], p = divmod(p, q)
        b[k], r = divmod(r, q)
    return a[i - 1] == b[j - 1] and a[j - 1] == b[i - 1] and a[i: j - 1] == b[i: j - 1]

find = False
for d in xrange(1, 10):
    p = (10 ** (j - i) - 1) * d;
    q = 10 ** j * (k - 1)
    g = gcd(p, q)
    p, q = p / g, q / g
    if check(p, q, i, j, k):
        print p, q
        find = True
        break
if not find:
    print "NO SOLUTION"
