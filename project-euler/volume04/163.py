def mod(n, m):
    return n % m

def T(n):
    return (1678 * n ** 3 + 3117 * n ** 2 + 88 * n - 345 * mod(n, 2) - 320 * mod(n, 3) - 90 * mod(n, 4) - 288 * mod(n ** 3 - n ** 2 + n, 5)) / 240

print T(1)
print T(2)
print T(36)
