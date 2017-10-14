from fractions import *
n = int(raw_input())
s = 1
while n > 0:
    a = map(int, raw_input().split())
    n -= len(a)
    for x in a:
        s = s * x / gcd(s, x)
b = []
while s:
    b.append(s % 26)
    s /= 26
b = [chr(x + ord('a')) for x in b]
b.reverse()
print 'a' * len(b)
print ''.join(b)
