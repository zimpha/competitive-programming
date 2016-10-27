def run(n, m):
    cycle = [0, 1]
    sum = 0
    for i in xrange(2, m * 6):
        sum += (i - 1) * cycle[i - 1]
        cycle.append(sum % i)
    cycle = cycle[1:] + cycle[:1]
    q, r = divmod(n, m * 6)
    for i in xrange(1, m * 6):
        cycle[i] = (cycle[i - 1] + cycle[i]) % m
    freq = [0] * m
    freq[0] = 1
    for i in xrange(m * 6):
        if i < r:
            freq[cycle[i]] += 1
        freq[cycle[i]] += q
    ret = 0
    for i in freq:
        ret += i * (i - 1) / 2
    return ret

assert run(10, 10) == 4, run(10, 10)
assert run(10 ** 4, 10 ** 3) == 97158, run(10 ** 4, 10 ** 3)
print run(10 ** 12, 10 ** 6)
