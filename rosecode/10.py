from itertools import *

ret = 0
for p in permutations(range(6)):
    find = True
    for i in xrange(6):
        for j in xrange(i):
            if i + p[i] == j + p[j] or i - p[i] == j - p[j]:
                find = False
    ret += find
print ret
