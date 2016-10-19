from math import log

def run(n):
  x = log(log(n)+0.57721566490153286060651209,10)-n*log(2,10)
  return int(pow(10, 7 + x-int(x)))

print run(123456789)

