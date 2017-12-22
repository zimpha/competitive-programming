from math import *

def totient_function():
    n = 100064101
    r = 0
    for i in xrange(n):
        r += log(i + 1)
    r /= log(10)
    return int(r) + 1

print totient_function()
