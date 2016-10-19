from decimal import *

getcontext().prec = 102
ret = 0
d = 100
p = pow(10, d - 1)
for n in xrange(1, 101):
  q = Decimal(n).sqrt()
  ret += sum(int(c) for c in str(q * p)[:d]) if  q % 1 != 0 else 0
print ret
