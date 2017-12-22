def phi(n):
    r, i = n, 2
    while i * i <= n:
        if n % i == 0:
            r = r / i * (i - 1)
            while n % i == 0:
                n /= i
        i += 1
    if n > 1:
        r = r / n * (n - 1)
    return r

def polynomial_expansion_2():
    # 15^k mod 100086841
    mod = 100086841
    p1 = phi(mod)
    p2 = phi(p1)
    e = pow(18, pow(10, 18, p2), p1)
    return pow(15, e, mod)

print polynomial_expansion_2()
