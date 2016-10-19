import itertools as it

def ok(a, b):
    s = [[0, 1], [0, 4], [0, 6], [1, 6], [2, 5], [3, 6], [4, 6], [6, 4], [8, 1]]
    for x in s:
        if x[0] in a and x[1] in b:
            continue
        if x[1] in a and x[0] in b:
            continue
        return 0
    return 1

co = it.combinations([0,1,2,3,4,5,6,7,8,6], 6)
l = []
for x in co:
    l.append(x)
print len(l)
ret = 0
for a in l:
    for b in l:
        ret += ok(a, b)
print ret / 2
