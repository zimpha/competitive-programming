import math

def M(C, R):
    if C > R:
        return R + 1
    tc = C - 2
    for i in xrange(C, R + 1):
        C = int(2 * math.ceil((C - 1.0) / tc) + C - 1)
    return C

def run(cl, cr, R):
    ret = 0
    for i in xrange(cl, cr + 1):
        ret += M(i, R)
    return ret

assert M(3, 6) == 123
assert M(4, 6) == 23
assert run(3, 4, 6) == 146
assert run(3, 10, 10) == 10382
print run(3, 40, 30)
