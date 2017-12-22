def D(n):
    r = 1e9
    for mask in xrange(1 << n):
        now = 0
        for i in xrange(n):
            if (mask >> i) & 1:
                now += i + 1
            else:
                now -= i + 1
        if now >= 0:
            r = min(r, now)
    return r

def S(n):
    # [0, 1, 1, 0]
    return n / 4 * 2 + n % 4 - (n % 4 == 3)

print S(19216812112)
