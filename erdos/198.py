def xor_again(n, mod):
    n += 1
    bits = [int(x) for x in bin(n)[2:]]
    m = len(bits)
    cnt = [[0] * m, [0] * m]
    for i in xrange(m):
        if not bits[i]: continue
        cnt[0][i] += 2 ** (m - i - 1)
        for j in xrange(i):
            cnt[bits[j]][j] += 2 ** (m - i - 1)
        for j in xrange(i + 1, m):
            cnt[0][j] += 2 ** (m - i - 2)
            cnt[1][j] += 2 ** (m - i - 2)
    ret = 0
    for i in xrange(m):
        ret += 2 ** (m - 1 - i) * cnt[0][i] * cnt[1][i] * 2
    return ret % mod

print xor_again(1073742824, 10 ** 9 + 7)
