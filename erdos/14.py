def count_fibonacci():
    a, b = 0, 1
    fib = set()
    for i in xrange(100):
        fib.add(a)
        c = a + b
        a, b = b, c
    with open('14.txt', 'r') as fp:
        a = map(int, fp.readlines())
        ret = sum([x in fib for x in a])
    return ret

print count_fibonacci()
