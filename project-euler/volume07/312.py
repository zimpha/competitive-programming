def euler_phi(n):
    r, i = n, 2
    while i * i <= n:
        if n % i != 0:
            i += 1
            continue
        r = r / i * (i - 1)
        while n % i == 0:
            n /= i
        i += 1
    if n > 1:
        r = r / n * (n - 1)
    return r

def run(d, n, mod):
    if d == 5:
        return (pow(3, n - 2, mod * 2) - 3 + mod * 2) % (mod * 2) / 2
    if d % 2 == 0:
        phi = euler_phi(mod)
        return 8 * pow(12, run(d + 1, n, phi) + phi, mod) % mod
    else:
        phi = euler_phi(mod * 2)
        return (pow(3, run(d + 1, n, phi) + phi - 2, mod * 2) - 3 + mod * 2) % (mod * 2) / 2

print run(0, 10000, 13 ** 8)
