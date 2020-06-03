from random import shuffle
from fractions import gcd

T = input()
for _ in range(T):
    n = input()
    ret = int(n)
    n = [ord(x) - ord('0') for x in n]
    for _ in range(250):
        shuffle(n)
        r = 0
        for x in n:
            r = r * 10 + x
        ret = gcd(ret, r)
    print(ret)
