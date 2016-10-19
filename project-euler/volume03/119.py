ls = []
for a in xrange(2, 1000):
    for b in xrange(2, 50):
        c = str(a ** b)
        s = 0
        for x in c:
            s += ord(x) - ord('0')
        if s == a:
            ls.append(a ** b)
ls.sort()
print ls[1]
print ls[9]
print ls[29]
