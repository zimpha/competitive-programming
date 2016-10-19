import math

def isPrime(n):
    if n < 2:
        return False
    if n <= 3:
        return True
    if n % 2 == 0:
        return False
    upp = min(n, int(math.sqrt(n)) + 10)
    for i in xrange(3, upp, 2):
        if n % i == 0:
            return False
    return True

sum, cnt = 0, 0
for i in xrange(2, 200000):
    if isPrime(i) and pow(10, 10 ** 9, i * 9) == 1:
        cnt += 1
        sum += i
        if cnt == 40:
            break
print sum
