def fives_and_sevens():
    ret = 0
    for mask in xrange(1 << 20):
        n = 0
        for i in xrange(20):
            if mask >> i & 1:
                n = n * 10 + 5
            else:
                n = n * 10 + 7
        if n % 5 == 0 and n % 7 == 0:
            ret += 1
    return ret

print fives_and_sevens()
