from decimal import *

def ok(s):
    for i in xrange(1, 10):
        if not chr(i + 48) in s:
            return False
    return True

f1, f2 = 1, 1
md = 1000000000
ret = 2
while True:
    ret += 1
    fn = (f1 + f2) % md
    f1, f2 = f2, fn
    if ok(str(fn)):
        t = ret * Decimal(0.20898764024997873) - Decimal(0.3494850021680094)
        t = 10 ** (t - int(t) + 8)
        if ok(str(int(t))):
            break
print ret
