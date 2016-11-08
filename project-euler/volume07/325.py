mod = 282475249
i2 = 141237625
f, g = [1, 2], [2, 3]
sg, sg2 = [2, 5], [4, 13]
sxg = [2, 8]

for i in xrange(2, 100):
    f.append(f[i - 1] + f[i - 2])
    g.append(g[i - 1] + g[i - 2])
    sg.append((sg[i - 1] + sg[i - 2] + g[i - 1] * f[i - 2]) % mod)
    sg2.append((sg2[i - 1] + sg2[i - 2] + g[i - 1] ** 2 * f[i - 2] + 2 * g[i - 1] * sg[i - 2]) % mod)
    sxg.append((sxg[i - 1] + sxg[i - 2] + g[i - 1] * f[i - 1] * f[i - 2] + g[i - 1] * (1 + f[i - 2]) * f[i - 2] / 2 + f[i - 1] * sg[i - 2]) % mod)

def wythoff(n):
    if n == 1:
        return 1
    n -= 1
    m = 0
    while f[m] <= n:
        m += 1
    m -= 1
    val = g[m]
    n -= f[m]
    m -= 1
    while n > 0:
        if n >= f[m]:
            n -= f[m]
            val += g[m]
        m -= 1
    return val + 1

def get_index(n):
    left, right = 1, n
    while left < right:
        mid = (left + right - 1) / 2
        if wythoff(mid) >= n:
            right = mid
        else:
            left = mid + 1
    return left

def run(n):
    m = get_index(n)
    ret = (n * n - m * m) * (n + 1 - m)
    n, m = m - 2, 0
    while f[m] <= n:
        m += 1
    m -= 1
    a, b, c, d, e = f[m], g[m], sg[m], sg2[m], sxg[m]
    n -= f[m]
    m -= 1
    while n > 0:
        if n >= f[m]:
            e = (e + sxg[m] + b * a * f[m] + b * (1 + f[m]) * f[m] / 2 + a * sg[m]) % mod
            d = (d + sg2[m] + b ** 2 * f[m] + 2 * b * sg[m]) % mod
            c = (c + sg[m] + b * f[m]) % mod
            b = (b + g[m]) % mod
            a += f[m]
            n -= f[m]
        m -= 1
    return (ret + d + 2 * e + c * 5 - a * (a + 1) * (a + 3)) * i2 % mod

print run(10)
print run(10 ** 4)
print run(10 ** 16)
