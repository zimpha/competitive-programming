import math

def solve(r1, r2, r3, n):
    if r1 * r2 * r3 != n:
        return 0
    return (r1 - 1) * (r2 - 1) * (r3 - 1)

def run(n):
    divisors = []
    m = int(math.sqrt(n))
    for i in xrange(1, m + 1):
        if n % i == 0:
            divisors.append(i)
            divisors.append(n / i)
            divisors.append(-i)
            divisors.append(-n / i)
    ret = 0
    for a in divisors:
        for b in divisors:
            for c in divisors:
                if a > b or b > c or a > c:
                    continue
                ret += solve(a, b, c, n)
    return ret

print run(18811938)
