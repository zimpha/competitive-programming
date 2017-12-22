def palindromes(n):
    def valid(x):
        h = hex(x)[2:]
        o = oct(x)[1:]
        return x <= n and h == h[::-1] and o == o[::-1]

    m = len(bin(n)[2:])
    ret = 0
    for l in xrange(1, m + 1):
        s = (l + 1) / 2
        for mask in xrange(1 << (s - 1)):
           v = mask | (1 << (s - 1))
           v = bin(v)[2:]
           x = int(v + v[:(-1 if l % 2 else s)][::-1], 2)
           if valid(x):
               ret += x
    return ret

print palindromes(10 ** 9)
