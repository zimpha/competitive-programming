from fractions import *

def lcm(a, b): return a * b // gcd(a, b)

def r(a, b):
    a %= b
    mp = {}
    mp[a] = 0
    for i in range(1, 10000):
        a = a * 2 % b;
        if a in mp:
            return i - mp[a]
        mp[a] = i
    return -1

def convert(a, b):
    digits = {}
    u, a = divmod(a, b)
    for i in range(63):
        digits[i] = u >> i & 1
    for i in range(1, 400):
        digits[-i], a = divmod(a * 2, b)
    return digits

def solve(a, b, c, d, ra, rb, rc, rd):
    r = {}
    for i in range(-1, 61):
        r[i] = 0
    fa, fb, fc, fd = False, False, False, False
    cnt, L = -1, 0
    for i in range(60, -400, -1):
        oa = 0 if fa else a[i]
        ob = 1 if fb else b[i]
        oc = 0 if fc else c[i]
        od = 1 if fd else d[i]
        if oa == 0 and ob == 0 and oc == 0 and od == 0:
            r[i] = 0
        elif oa == 0 and ob == 0 and oc == 1 and od == 1:
            r[i] = 1
        elif oa == 1 and ob == 1 and oc == 0 and od == 0:
            r[i] = 1
        elif oa == 1 and ob == 1 and oc == 1 and od == 1:
            r[i] = 0
        elif oa == 0 and ob == 0 and oc == 0 and od == 1:
            if not fc: cnt = 0
            r[i], fc, rc = 1, True, 1
        elif oa == 1 and ob == 1 and oc == 0 and od == 1:
            if not fd: cnt = 0
            r[i], fd, rd = 1, True, 1
        elif oa == 0 and ob == 1 and oc == 0 and od == 0:
            if not fa: cnt = 0
            r[i], fa, ra = 1, True, 1
        elif oa == 0 and ob == 1 and oc == 1 and od == 1:
            if not fb: cnt = 0
            r[i], fb, rb = 1, True, 1
        else:
            r[i] = 2
            L = 0
            break
        L = lcm(lcm(ra, rb), lcm(rc, rd))
        if i < -10 and cnt == -1: cnt = 0
        if i < -10: cnt += 1
        if cnt == L + 1: break
    bits = min(r.keys())
    x, y = 0, 2 ** (-bits)
    for i in range(61):
        x += r[i] * 2 ** i
    x *= y
    for i in range(0, -bits):
        x += r[i + bits] * 2 ** i
    assert L < -bits
    if L == 0: return x, y
    u, v = x >> L, y >> L
    y >>= L
    return x * v - u * y, v * y * (2 ** L - 1)

for _ in range(int(input())):
    an, ad, bn, bd = map(int, input().split())
    cn, cd, dn, dd = map(int, input().split())
    a = convert(an, ad)
    b = convert(bn, bd)
    c = convert(cn, cd)
    d = convert(dn, dd)
    xn, xd = solve(a, b, c, d, r(an, ad), r(bn, bd), r(cn, cd), r(dn, dd))
    g = gcd(xn, xd)
    print(xn // g, xd // g)
