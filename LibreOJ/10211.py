mod = 9901

a, b = map(int, input().split())
if a == 0:
    print(0)
    exit(0)
p = []
i = 2
while i * i <= a:
    if a % i == 0:
        c = 0
        while a % i == 0:
            c += 1
            a //= i
        p.append((i, c * b))
    i += 1
if a > 1:
    p.append((a, b))
r = 1
for (i, e) in p:
    inv = pow(i - 1, mod - 2, mod)
    r = r * inv * (pow(i, e + 1, mod) - 1 + mod) % mod
print(r)
