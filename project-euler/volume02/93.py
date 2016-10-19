import itertools as it

def op(a, b, c):
    if a == None or b == None:
        return None
    if c == 0:
        return a + b
    if c == 1:
        return a - b
    if c == 2:
        return a * b
    if b == 0:
        return None
    return 1.0 * a / b

def calc(x):
    perm = it.permutations(x)
    res = [0] * 10000
    for x in perm:
        a, b, c, d = x[0], x[1], x[2], x[3]
        for i in xrange(4):
            for j in xrange(4):
                for k in xrange(4):
                    n = op(op(a, b, i), op(c, d, k), j)
                    if n != None and n == int(n) and n >= 0:
                        res[int(n)] = 1
                    n = op(op(a, op(b, c, j), i), d, k)
                    if n != None and n == int(n) and n >= 0:
                        res[int(n)] = 1
                    n = op(a, op(op(b, c, j), d, k), i)
                    if n != None and n == int(n) and n >= 0:
                        res[int(n)] = 1
                    n = op(op(op(a, b, i), c, j), d, k)
                    if n != None and n == int(n) and n >= 0:
                        res[int(n)] = 1
                    n = op(a, op(b, op(c, d, k), j), i)
                    if n != None and n == int(n) and n >= 0:
                        res[int(n)] = 1
    l = 1
    while res[l] == 1:
        l += 1
    return l - 1

co = it.combinations([0,1,2,3,4,5,6,7,8,6], 4)
ret = 0
for x in co:
    tmp = calc(x)
    if tmp > ret:
        ret = tmp
        ls = x
print ls, ret
