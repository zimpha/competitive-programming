def number_spiral_diagonals(n):
    ret = 0
    for i in xrange(1, n + 1):
        ret += i * i - i + 1
        ret += (3 + 4 * (i - 1) + 2 * (i - 1) ** 2 - (1 if i % 2 else -1)) / 2
    return ret - 1

print number_spiral_diagonals(5)
print number_spiral_diagonals(10001)
