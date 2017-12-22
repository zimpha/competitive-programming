def large_exponentiation():
    p = 1
    for i in xrange(2097152):
        if p == 1 and i:
            return i
        p = p * 201413 % 2097152
    return -1

print large_exponentiation()
