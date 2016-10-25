import primesieve as ps

def rep(n):
    # assume gcd(n, 6) = 1
    p = 1
    while p <= n:
        p *= 3
    p /= 3
    n -= p
    if n == 0:
        return [p]
    mul = 1
    while n % 2 == 0:
        mul *= 2
        n /= 2
    r = rep(n)
    r = [x * mul for x in r]
    r.append(p)
    return r

def is_unique(n):
    if n in [2, 3]:
        return True
    r = rep(n)
    #print n, r
    if len(r) > 4:
        return False
    elif len(r) == 4:
        x2, x3 = r[1], r[2]
        return n < min(r[0] * 4, r[3] * 3) and 3 * x2 > x3 + r[3] and 2 * x3 > r[0] + x2
    elif len(r) == 3:
        return n < min(r[0] * 4, r[2] * 3) and r[1] > max(r[0] / 2, r[2] / 3)
    elif len(r) == 2:
        return n < min(r[0] * 4, r[1] * 3)
    return False

def run(n):
    pl = ps.generate_primes(n)
    ret = 0
    for q in pl:
        if is_unique(q):
            ret += q
    return ret

print run(10 ** 2)
print run(10 ** 6)
