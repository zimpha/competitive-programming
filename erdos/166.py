def apples_for_ryuk(n):
    # sum_{i=1}^{n} (2^(2^n) + 1) mod 9
    x, y = divmod(n, 2)
    return x * 13 + y * 5

print apples_for_ryuk(999999999999)
