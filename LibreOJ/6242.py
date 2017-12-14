# Ramanujan's factorial approximation
from math import *
from decimal import *

getcontext().prec = 120

pi = Decimal('3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481')

n, k = map(int, raw_input().split())

res = (pi.ln() / Decimal(2) + n * Decimal(n).ln() - n + (Decimal(8 * n ** 3 + 4 * n ** 2 + n) + Decimal(1.0) / Decimal(30)).ln() / Decimal(6)) / Decimal(10).ln()
digits = int(res)
res = Decimal(10) ** (res - digits)
if n <= 20:
    res = 1
    for i in xrange(n):
        res *= i + 1
    res /= 10. ** digits
res = ('%.*f' % (k - 1, res)).rstrip('0')
if digits == 0:
    res = res.rstrip('.')
print '%se+%d' % (res, digits)
