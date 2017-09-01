def check(n):
    s = [2, 3, 4, 7]
    while n:
        if not (n % 10) in s: return False
        n /= 10
    return True

ret = 0
for a in xrange(100, 1000):
    if not check(a): continue
    for b in [2, 3, 5, 7]:
        for c in [2, 3, 5, 7]:
            if not check(a * b) or not check(a * c): continue
            if check(a * (b * 10 + c)):
                ret += 1
print ret
