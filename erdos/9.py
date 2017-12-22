def highly_divisible_number(bound):
    n = 3 * 10 ** 6
    d = [0] * n
    for i in xrange(1, n):
        for j in xrange(i, n, i):
            d[j] += 1
    for i in xrange(1, n):
        if d[i] > bound:
            return i
    return -1

print highly_divisible_number(300)
